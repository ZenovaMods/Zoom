; This file was automatically generated using tools/process_symbol_map.py
; Tue May 24 2022 21:13:02 UTC
bits 64
SECTION .data
extern _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr
extern __applyTurnDelta_LocalPlayer__QEAAXAEBUVec2___Z_ptr
extern _getSensitivity_Options__QEBAMW4InputMode___Z_ptr
extern _getCurrentInputMode_IClientInstance__QEAA_AW4InputMode__XZ_ptr

SECTION .text
global ?getFov@LevelRendererPlayer@@QEAAMM_N@Z
?getFov@LevelRendererPlayer@@QEAAMM_N@Z:
	jmp qword [rel _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr]
global ?_applyTurnDelta@LocalPlayer@@QEAAXAEBUVec2@@@Z
?_applyTurnDelta@LocalPlayer@@QEAAXAEBUVec2@@@Z:
	jmp qword [rel __applyTurnDelta_LocalPlayer__QEAAXAEBUVec2___Z_ptr]
global ?getSensitivity@Options@@QEBAMW4InputMode@@@Z
?getSensitivity@Options@@QEBAMW4InputMode@@@Z:
	jmp qword [rel _getSensitivity_Options__QEBAMW4InputMode___Z_ptr]
global ?getCurrentInputMode@IClientInstance@@QEAA?AW4InputMode@@XZ
?getCurrentInputMode@IClientInstance@@QEAA?AW4InputMode@@XZ:
	jmp qword [rel _getCurrentInputMode_IClientInstance__QEAA_AW4InputMode__XZ_ptr]
