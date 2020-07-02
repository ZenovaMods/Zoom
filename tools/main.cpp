// This file was automatically generated using tools/process_csv.py
// Generated on Thu Jul 02 2020 16:52:34 UTC

#include <Zenova/Hook.h>


extern "C" {
	void* _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr;
}

void InitBedrockPointers() {
	_getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr = reinterpret_cast<void*>(Zenova::Hook::FindSymbol("?getFov@LevelRendererPlayer@@QEAAMM_N@Z"));
}

#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved) {
	if(fdwReason == DLL_PROCESS_ATTACH) InitBedrockPointers();
	return TRUE;
}
