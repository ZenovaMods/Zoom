// This file was automatically generated using tools/process_csv.py
// Generated on Sun Jun 07 2020 23:09:46 UTC

#include <Zenova/Hook.h>

extern "C" {
	void* _registerButtonDownHandler_InputHandler__QEAAXV_$basic_string_DU_$char_traits_D_std__V_$allocator_D_2__std__V_$function_$$A6AXW4FocusImpact__AEAVIClientInstance___Z_3__N_Z_ptr;
	void* _registerButtonUpHandler_InputHandler__QEAAXV_$basic_string_DU_$char_traits_D_std__V_$allocator_D_2__std__V_$function_$$A6AXW4FocusImpact__AEAVIClientInstance___Z_3__N_Z_ptr;
}

void InitBedrockPointers() {
	_registerButtonDownHandler_InputHandler__QEAAXV_$basic_string_DU_$char_traits_D_std__V_$allocator_D_2__std__V_$function_$$A6AXW4FocusImpact__AEAVIClientInstance___Z_3__N_Z_ptr = reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x19597B0));
	_registerButtonUpHandler_InputHandler__QEAAXV_$basic_string_DU_$char_traits_D_std__V_$allocator_D_2__std__V_$function_$$A6AXW4FocusImpact__AEAVIClientInstance___Z_3__N_Z_ptr = reinterpret_cast<void*>(Zenova::Hook::SlideAddress(0x1959900));
}

#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved) {
	if(fdwReason == DLL_PROCESS_ATTACH) InitBedrockPointers();
	return TRUE;
}
