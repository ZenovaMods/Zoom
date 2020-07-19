#include "Zenova.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>

#include "Zenova/Minecraft/Inputs.h"

//Globals
bool zoomEnabled = false;
bool smoothCameraEnabled = false;

//Zoom
class LevelRendererPlayer {
public:
	float getFov(float, bool);
};

float (*_getFov)(LevelRendererPlayer*, float, bool);
float getFov(LevelRendererPlayer* self, float f, bool b) {
	float fov = _getFov(self, f, b);

	/* animation method
	constexpr float zoomValue = 0.75f;
	static float animValue = 0.0f;
	if(zoomEnabled)
		animValue = std::min(animValue + (f * 0.1f), 1.0f);
	else
		animValue = std::max(animValue - (f * 0.1f), 0.0f);

	fov -= (animValue * animValue * zoomValue * fov);
	*/
	
	//optifine method
	if(zoomEnabled) {
		fov /= 4.0f;
	}

	return std::min(std::max(fov, 1.0f), 179.0f);
}

void handleZoomButton(bool pressed) {
	zoomEnabled = pressed;
	smoothCameraEnabled = pressed;
}

//Cinematic Camera
class InputFilter {
	//not sure how the java team names their variables
	float pre;
	float delta;
	float post;

public:
	InputFilter() { reset(); }

	//don't really understand what smoothing method is being used
	float smooth(float f, float amount) {
		pre += f;
		f = (pre - delta) * amount;
		post += (f - post) * 0.5F;

		if ((f > 0.0F && f > post) || (f < 0.0F && f < post))
		{
			f = post;
		}

		delta += f;
		return f;
	}

	void reset() {
		pre = 0.0f;
		delta = 0.0f;
		post = 0.0f;
	}
};

struct Vec2 {
	float x, y;
};

class LocalPlayer {
public:
	//was probably private
	void _applyTurnDelta(const Vec2& input);
};

//Options::getSensitivity(ClientInstance::getCurrentInputMode());
static inline float mouseSensitivity = 0.25f;

void (*_applyTurnDelta)(class LocalPlayer*, const Vec2&);
void applyTurnDelta(class LocalPlayer* self, const Vec2& input) {
	static InputFilter filterX, filterY;
	Vec2 smooth;

	if (smoothCameraEnabled) {
		float f = std::pow((mouseSensitivity * 0.6f) + 0.2f, 3) * 8.0f;
		smooth.x = filterX.smooth(input.x * f, f * 0.05f);
		smooth.y = filterY.smooth(input.y * f, f * 0.05f);
	}
	else {
		smooth = input;

		filterX.reset();
		filterY.reset();
	}

	_applyTurnDelta(self, smooth);
}

void handleCinematicButton(bool pressed) {
	if (pressed) {
		smoothCameraEnabled = !smoothCameraEnabled;
	}
}

class Zoom : public Zenova::Mod {
	virtual void Start() {
		Zenova::Platform::DebugPause();

		Zenova::InputManager::addInput("zoom", &handleZoomButton)
			.setKeyboardMapping('C')
			.setGamepadMapping(GamepadBinding::DpadLeft);

		Zenova::InputManager::addInput("cinematic", &handleCinematicButton)
			.setKeyboardMapping(KeyboardBinding::F10);

		Zenova::Hook::Create(&LevelRendererPlayer::getFov, &getFov, &_getFov);
		Zenova::Hook::Create(&LocalPlayer::_applyTurnDelta, &applyTurnDelta, &_applyTurnDelta);
	}

	virtual void Update() {}
	virtual void Tick() {}
	virtual void Stop() {}
	virtual ~Zoom() {}
};

MOD_FUNCTION Zenova::Mod* CreateMod() {
	return new Zoom;
}
