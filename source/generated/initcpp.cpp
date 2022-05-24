// This file was automatically generated using tools/process_symbol_map.py
// Tue May 24 2022 21:13:02 UTC

#include <Zenova/Hook.h>
#include <Zenova/Minecraft.h>

#include "initcpp.h"

using namespace Zenova::Hook;


extern "C" {
	void* _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr;
	void* __applyTurnDelta_LocalPlayer__QEAAXAEBUVec2___Z_ptr;
	void* _getSensitivity_Options__QEBAMW4InputMode___Z_ptr;
	void* _getCurrentInputMode_IClientInstance__QEAA_AW4InputMode__XZ_ptr;
}

void InitBedrockPointers() {
	_getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr = reinterpret_cast<void*>(SigscanCall("\xE8\x00\x00\x00\x00\x0F\x28\xF0\xF3\x44\x0F\x10\x3D\x00\x00\x00\x00", "x????xxxxxxxx????"));
	__applyTurnDelta_LocalPlayer__QEAAXAEBUVec2___Z_ptr = reinterpret_cast<void*>(SigscanCall("\xE8\x00\x00\x00\x00\x48\x8B\x4D\x20\x48\x33\xCC\xE8\x00\x00\x00\x00\x44\x0F\x28\xAC\x24\x00\x00\x00\x00", "x????xxxxxxxx????xxxxx????"));
	_getSensitivity_Options__QEBAMW4InputMode___Z_ptr = reinterpret_cast<void*>(SigscanCall("\xE8\x00\x00\x00\x00\xF3\x0F\x10\x0D\x00\x00\x00\x00\x0F\x2F\xC1\x72\x09", "x????xxxx????xxxxx"));
	_getCurrentInputMode_IClientInstance__QEAA_AW4InputMode__XZ_ptr = reinterpret_cast<void*>(Sigscan("\x40\x53\x48\x83\xEC\x20\x48\x8B\x01\xFF\x90\x00\x00\x00\x00\x48\x8B\x08", "xxxxxxxxxxx????xxx"));
}

void InitVersionPointers() {
	const Zenova::Version& versionId = Zenova::Minecraft::version();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved) {
	if(fdwReason == DLL_PROCESS_ATTACH) {
		InitBedrockPointers();
		InitVersionPointers();
	}
	return TRUE;
}
