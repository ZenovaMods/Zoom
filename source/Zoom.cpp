#include "Zenova.h"

#include <algorithm>
#include <cmath>

#include "Zenova/Minecraft/Inputs.h"

// Globals
static inline bool zoomEnabled = false;
static inline bool smoothCameraEnabled = false;

// Zoom
class LevelRendererPlayer {
public:
	float getFov(float, bool);
};

float (*_getFov)(LevelRendererPlayer*, float, bool);
float getFov(LevelRendererPlayer* self, float f, bool b) {
	float fov = _getFov(self, f, b);

#ifdef USE_OPTIFINE
	// optifine method
	if (zoomEnabled) {
		fov /= 4.0f;
	}
#else
	// animation method from mcmrarm
	constexpr float zoomValue = 0.75f;
	static float animValue = 0.0f;
	if (zoomEnabled)
		animValue = std::min(animValue + (f * 0.1f), 1.0f);
	else
		animValue = std::max(animValue - (f * 0.1f), 0.0f);

	fov -= (animValue * animValue * zoomValue * fov);
#endif // OPTIFINE

	return std::min(std::max(fov, 1.0f), 179.0f);
}

void handleZoomButton(bool pressed) {
	zoomEnabled = pressed;
	smoothCameraEnabled = pressed;
}

// Cinematic Camera
class SmoothFloat {
	float targetValue = 0.0f;
	float remainingValue = 0.0f;
	float lastAmount = 0.0f;

public:
	// todo: figure out the reasoning behind this, mojang's implementation
	float getNewDeltaValue(float target, float delta) {
		targetValue += target;
		float currentValue = targetValue - remainingValue;
		float amount = lastAmount + 0.5f * (currentValue - lastAmount); // lerp

		float sign = static_cast<float>((0.0f < currentValue) - (currentValue < 0.0f)); // signum
		if (sign * currentValue > sign * lastAmount) {
			currentValue = amount;
		}

		lastAmount = amount;
		remainingValue += currentValue * delta;
		return currentValue * delta;
	}

	void reset() {
		targetValue = 0.0f;
		remainingValue = 0.0f;
		lastAmount = 0.0f;
	}
};

struct Vec2 {
	float x, y;
};

enum class InputMode : char;

class Options {
public:
	float getSensitivity(InputMode) const;
};

class IClientInstance {
public:
#define NUM_WIDGETS 155
#include "VFuncFiller.h"
	virtual Options& getOptions();
	
	// virtual function
	InputMode getCurrentInputMode();
};

class LocalPlayer {
	char filler1[0x1F58];
	IClientInstance& client_1_16;
	char filler2[0x1E0];
	IClientInstance& client_1_14;

public:
	IClientInstance& getClientInstance() {
		if (Zenova::Minecraft::version() == Zenova::Minecraft::v1_14_60_5) {
			return client_1_14;
		}
		else {
			return client_1_16;
		}
	}

	// was probably private
	void _applyTurnDelta(const Vec2& input);
};

void (*_applyTurnDelta)(class LocalPlayer*, const Vec2&);
void applyTurnDelta(class LocalPlayer* self, const Vec2& input) {
	static SmoothFloat filterX, filterY;
	Vec2 smoothCam;
	IClientInstance& client = self->getClientInstance();

	if (smoothCameraEnabled) {
		// todo: figure out the reasoning behind mojang's implementation
		constexpr float deltaTime = (1.0f / 20.0f); // todo: grab the passed time properly?
		float sensitivity = client.getOptions().getSensitivity(client.getCurrentInputMode());
		float f = std::pow((sensitivity * 0.6f) + 0.2f, 3.0f) * 8.0f;

		smoothCam.x = filterX.getNewDeltaValue(input.x * f, deltaTime * f);
		smoothCam.y = filterY.getNewDeltaValue(input.y * f, deltaTime * f);
	}
	else {
		filterX.reset();
		filterY.reset();

		smoothCam = input;
	}

	_applyTurnDelta(self, smoothCam);
}

void handleCinematicButton(bool pressed) {
	if (pressed) {
		smoothCameraEnabled = !smoothCameraEnabled;
	}
}

class Zoom : public Zenova::Mod {
	virtual void Start() {
		Zenova::Platform::DebugPause();

		Zenova::InputManager::addInput("zenova.zoom", &handleZoomButton)
			.setKeyboardMapping('C')
			.setGamepadMapping(GamepadBinding::DpadLeft);

		Zenova::InputManager::addInput("zenova.cinematic", &handleCinematicButton)
			.setKeyboardMapping(KeyboardBinding::F7);

		Zenova_Hook(LevelRendererPlayer::getFov, &getFov, &_getFov);
		Zenova_Hook(LocalPlayer::_applyTurnDelta, &applyTurnDelta, &_applyTurnDelta);
	}

	virtual void Update() {}
	virtual void Tick() {}
	virtual void Stop() {}
	virtual ~Zoom() {}
};

MOD_FUNCTION Zenova::Mod* CreateMod() {
	return new Zoom;
}
