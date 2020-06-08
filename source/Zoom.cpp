#include "Zenova.h"

#include "InputHeaders.h"

#include <unordered_map>
#include <iostream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>

static bool zoomEnabled = false;
static float zoomValue = 0.75f;

float (*_getFOV)(class LevelRendererPlayer*, float, bool);
float getFOV(class LevelRendererPlayer* self, float f, bool b) {
	float fov = _getFOV(self, f, b);

	//Zenova_Info(std::to_string(fov));

	static float animValue = 0.0f;
	if(zoomEnabled)
		animValue = std::min(animValue + (f * 0.1f), 1.0f);
	else
		animValue = std::max(animValue - (f * 0.1f), 0.0f);

	fov -= (animValue * animValue * zoomValue * fov);

	return std::min(std::max(fov, 1.0f), 179.0f);
}

//would've done invariant here but it would've allowed you to zoom in while sleep :P
void (*__addFullKeyboardGamePlayControls)(VanillaClientInputMappingFactory*, KeyboardInputMapping&, MouseInputMapping&);
void _addFullKeyboardGamePlayControls(VanillaClientInputMappingFactory* self, KeyboardInputMapping& keyboard, MouseInputMapping& mouse) {
	__addFullKeyboardGamePlayControls(self, keyboard, mouse);

	self->createKeyboardAndMouseBinding(keyboard, mouse, "button.zoom", "key.zoom");
}

namespace ClientInputMappingFactory { 
	enum class MappingControllerType : int {
		Xbox
	}; 
}

void (*__addInvariantGamePlayGameControllerControls)(VanillaClientInputMappingFactory*, GameControllerInputMapping&, ClientInputMappingFactory::MappingControllerType);
void _addInvariantGamePlayGameControllerControls(VanillaClientInputMappingFactory* self, GameControllerInputMapping& gamepad, ClientInputMappingFactory::MappingControllerType controllerType) {
	__addInvariantGamePlayGameControllerControls(self, gamepad, controllerType);

	switch(controllerType) {
	case ClientInputMappingFactory::MappingControllerType::Xbox:
		self->createGamepadBinding(gamepad, self->mXboxLayout, "button.zoom", "key.zoom");
		break;
	default:
		self->createGamepadBinding(gamepad, self->mGenericLayout, "button.zoom", "key.zoom");
		break;
	}
}

enum class RemappingType {
	Keyboard,
	Gamepad,
	None
};

inline RemappingType mapType;

enum XboxBinding {
	None,
	A,
	B,
	X,
	Y,
	DpadUp,
	DpadDown,
	DpadLeft,
	DpadRight,
	LS,
	RS,
	LB,
	RB,
	Select,
	Start,
	Touchpad,
	LeftTrigger = -100,
	RightTrigger
};

void (*_assignDefaultMapping)(RemappingLayout*, std::vector<Keymapping>&&);
void assignDefaultMapping(RemappingLayout* self, std::vector<Keymapping>&& mapping) {
	switch(mapType) {
		case RemappingType::Keyboard:
			mapping.emplace_back("key.zoom", 'C');
			break;

		case RemappingType::Gamepad:
			mapping.emplace_back("key.zoom", XboxBinding::DpadLeft);
			break;

		default: break;
	}

	_assignDefaultMapping(self, std::move(mapping));
}

void (*__populateKeyboardDefaults)(VanillaClientInputMappingFactory*, RemappingLayout&);
void _populateKeyboardDefaults(VanillaClientInputMappingFactory* self, RemappingLayout& a1) {
	mapType = RemappingType::Keyboard;
	__populateKeyboardDefaults(self, a1);
	mapType = RemappingType::None;
}

void (*__populateGamepadDefaults)(VanillaClientInputMappingFactory*, RemappingLayout&);
void _populateGamepadDefaults(VanillaClientInputMappingFactory* self, RemappingLayout& a1) {
	mapType = RemappingType::Gamepad;
	__populateGamepadDefaults(self, a1);
	mapType = RemappingType::None;
}

void handleZoomButtonPress() {
	zoomEnabled = true;
}

void handleZoomButtonRelease() {
	zoomEnabled = false;
}

void (*__registerInputHandlers)(MinecraftInputHandler*);
void _registerInputHandlers(MinecraftInputHandler* self) {
	__registerInputHandlers(self);
	self->mInput->registerButtonDownHandler("button.zoom", [](FocusImpact, IClientInstance&) { handleZoomButtonPress(); }, false);
	self->mInput->registerButtonUpHandler("button.zoom", [](FocusImpact, IClientInstance&) { handleZoomButtonRelease(); }, false);
}

void (*__handleDuplicates)(class ControlsSettingsScreenController*, class RemappingLayout&);
void _handleDuplicates(class ControlsSettingsScreenController* self, class RemappingLayout& a2) {}

class Zoom : public Zenova::Mod {
	virtual void Start() {
		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x1AA0FC0)), _populateKeyboardDefaults, (void**)&__populateKeyboardDefaults);
		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x1AA3860)), _populateGamepadDefaults, (void**)&__populateGamepadDefaults);
		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x07A4E20)), assignDefaultMapping, (void**)&_assignDefaultMapping); 

		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x1AAEB80)), _addFullKeyboardGamePlayControls, (void**)&__addFullKeyboardGamePlayControls);
		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x1AB07D0)), _addInvariantGamePlayGameControllerControls, (void**)&__addInvariantGamePlayGameControllerControls);

		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x079D610)), _registerInputHandlers, (void**)&__registerInputHandlers);
		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x0305470)), _handleDuplicates, (void**)&__handleDuplicates);

		Zenova::Platform::CreateHook(reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x0A76A20)), getFOV, (void**)&_getFOV);
	}

	virtual void Update() {}
	virtual void Tick() {}
	virtual void Stop() {}
	virtual ~Zoom() {}
};

MOD_FUNCTION Zenova::Mod* CreateMod() {
	return new Zoom;
}
