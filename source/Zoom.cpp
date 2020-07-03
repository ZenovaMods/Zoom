#include "Zenova.h"

#include <unordered_map>
#include <iostream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "Zenova/Minecraft/Inputs.h"

class LevelRendererPlayer {
public:
	float getFov(float, bool);
};

static bool zoomEnabled = false;
static float zoomValue = 0.75f;

float (*_getFov)(LevelRendererPlayer*, float, bool);
float getFov(LevelRendererPlayer* self, float f, bool b) {
	float fov = _getFov(self, f, b);

	/*
	static float animValue = 0.0f;
	if(zoomEnabled)
		animValue = std::min(animValue + (f * 0.1f), 1.0f);
	else
		animValue = std::max(animValue - (f * 0.1f), 0.0f);

	fov -= (animValue * animValue * zoomValue * fov);
	*/
	
	if(zoomEnabled) {
		fov /= 4.0f;
	}

	return std::min(std::max(fov, 1.0f), 179.0f);
}


void handleZoomButton(bool pressed) {
	if (pressed) {
		zoomEnabled = true;
	}
	else {
		zoomEnabled = false;
	}
}


class Zoom : public Zenova::Mod {
	virtual void Start() {
		Zenova::InputManager::instance().addInput("zoom", &handleZoomButton)
			.setKeyboardMapping('C')
			.setGamepadMapping(GamepadBinding::DpadLeft);

		Zenova::Hook::Create(&LevelRendererPlayer::getFov, &getFov, &_getFov);
	}

	virtual void Update() {}
	virtual void Tick() {}
	virtual void Stop() {}
	virtual ~Zoom() {}
};

MOD_FUNCTION Zenova::Mod* CreateMod() {
	return new Zoom;
}
