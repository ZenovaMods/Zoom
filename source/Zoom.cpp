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
static inline bool zoomEnabled = false;
static inline bool smoothCameraEnabled = false;

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
	float targetValue;
	float remainingValue;
	float lastAmount;

public:
	InputFilter() { reset(); }

	float smooth(float f, float amount) {
		targetValue += f;
		f = (targetValue - remainingValue) * amount;
		lastAmount += (f - lastAmount) * 0.5F;

		if (f != 0.0F && f != lastAmount) {
			f = lastAmount;
		}

		remainingValue += f;
		return f;
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

enum class InputMode : char {};

class Options {
public:
	float getSensitivity(InputMode) const;
};

class IClientInstance {
public:
	//maybe make this a macro?
	virtual void filler1() {}
	virtual void filler2() {}
	virtual void filler3() {}
	virtual void filler4() {}
	virtual void filler5() {}
	virtual void filler6() {}
	virtual void filler7() {}
	virtual void filler8() {}
	virtual void filler9() {}
	virtual void filler10() {}
	virtual void filler11() {}
	virtual void filler12() {}
	virtual void filler13() {}
	virtual void filler14() {}
	virtual void filler15() {}
	virtual void filler16() {}
	virtual void filler17() {}
	virtual void filler18() {}
	virtual void filler19() {}
	virtual void filler20() {}
	virtual void filler21() {}
	virtual void filler22() {}
	virtual void filler23() {}
	virtual void filler24() {}
	virtual void filler25() {}
	virtual void filler26() {}
	virtual void filler27() {}
	virtual void filler28() {}
	virtual void filler29() {}
	virtual void filler30() {}
	virtual void filler31() {}
	virtual void filler32() {}
	virtual void filler33() {}
	virtual void filler34() {}
	virtual void filler35() {}
	virtual void filler36() {}
	virtual void filler37() {}
	virtual void filler38() {}
	virtual void filler39() {}
	virtual void filler40() {}
	virtual void filler41() {}
	virtual void filler42() {}
	virtual void filler43() {}
	virtual void filler44() {}
	virtual void filler45() {}
	virtual void filler46() {}
	virtual void filler47() {}
	virtual void filler48() {}
	virtual void filler49() {}
	virtual void filler50() {}
	virtual void filler51() {}
	virtual void filler52() {}
	virtual void filler53() {}
	virtual void filler54() {}
	virtual void filler55() {}
	virtual void filler56() {}
	virtual void filler57() {}
	virtual void filler58() {}
	virtual void filler59() {}
	virtual void filler60() {}
	virtual void filler61() {}
	virtual void filler62() {}
	virtual void filler63() {}
	virtual void filler64() {}
	virtual void filler65() {}
	virtual void filler66() {}
	virtual void filler67() {}
	virtual void filler68() {}
	virtual void filler69() {}
	virtual void filler70() {}
	virtual void filler71() {}
	virtual void filler72() {}
	virtual void filler73() {}
	virtual void filler74() {}
	virtual void filler75() {}
	virtual void filler76() {}
	virtual void filler77() {}
	virtual void filler78() {}
	virtual void filler79() {}
	virtual void filler80() {}
	virtual void filler81() {}
	virtual void filler82() {}
	virtual void filler83() {}
	virtual void filler84() {}
	virtual void filler85() {}
	virtual void filler86() {}
	virtual void filler87() {}
	virtual void filler88() {}
	virtual void filler89() {}
	virtual void filler90() {}
	virtual void filler91() {}
	virtual void filler92() {}
	virtual void filler93() {}
	virtual void filler94() {}
	virtual void filler95() {}
	virtual void filler96() {}
	virtual void filler97() {}
	virtual void filler98() {}
	virtual void filler99() {}
	virtual void filler100() {}
	virtual void filler101() {}
	virtual void filler102() {}
	virtual void filler103() {}
	virtual void filler104() {}
	virtual void filler105() {}
	virtual void filler106() {}
	virtual void filler107() {}
	virtual void filler108() {}
	virtual void filler109() {}
	virtual void filler110() {}
	virtual void filler111() {}
	virtual void filler112() {}
	virtual void filler113() {}
	virtual void filler114() {}
	virtual void filler115() {}
	virtual void filler116() {}
	virtual void filler117() {}
	virtual void filler118() {}
	virtual void filler119() {}
	virtual void filler120() {}
	virtual void filler121() {}
	virtual void filler122() {}
	virtual void filler123() {}
	virtual void filler124() {}
	virtual void filler125() {}
	virtual void filler126() {}
	virtual void filler127() {}
	virtual void filler128() {}
	virtual void filler129() {}
	virtual void filler130() {}
	virtual void filler131() {}
	virtual void filler132() {}
	virtual void filler133() {}
	virtual void filler134() {}
	virtual void filler135() {}
	virtual void filler136() {}
	virtual void filler137() {}
	virtual void filler138() {}
	virtual void filler139() {}
	virtual void filler140() {}
	virtual void filler141() {}
	virtual void filler142() {}
	virtual void filler143() {}
	virtual void filler144() {}
	virtual void filler145() {}
	virtual void filler146() {}
	virtual void filler147() {}
	virtual void filler148() {}
	virtual void filler149() {}
	virtual void filler150() {}
	virtual void filler151() {}
	virtual void filler152() {}
	virtual void filler153() {}
	virtual void filler154() {}
	virtual void filler155() {}
	virtual void filler156() {}
	virtual Options& getOptions();
	
	//virtual function
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

	//was probably private
	void _applyTurnDelta(const Vec2& input);
};

void (*_applyTurnDelta)(class LocalPlayer*, const Vec2&);
void applyTurnDelta(class LocalPlayer* self, const Vec2& input) {
	static InputFilter filterX, filterY;
	Vec2 smoothCam;
	IClientInstance& client = self->getClientInstance();

	if (smoothCameraEnabled) {
		float f = ((client.getOptions().getSensitivity(client.getCurrentInputMode()) * 0.6f) + 0.2f) * 0.8f;

		smoothCam.x = filterX.smooth(input.x * f, f * 0.05f);
		smoothCam.y = filterY.smooth(input.y * f, f * 0.05f);
	}
	else {
		smoothCam = input;

		filterX.reset();
		filterY.reset();
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
