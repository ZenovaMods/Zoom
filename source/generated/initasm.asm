; This file was automatically generated using tools/process_headers.py
; Generated on Mon Jul 20 2020 03:58:10 UTC
bits 64
SECTION .data
extern _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr
extern __applyTurnDelta_LocalPlayer__QEAAXAEBUVec2___Z_ptr
extern _getSensitivity_Options__QEBAMW4InputMode___Z_ptr
extern _getCurrentInputMode_IClientInstance__QEAA_AW4InputMode__XZ_ptr

SECTION .text
global ?getFov@LevelRendererPlayer@@QEAAMM_N@Z
?getFov@LevelRendererPlayer@@QEAAMM_N@Z:
	mov rax, [rel _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr]
	jmp rax
global ?_applyTurnDelta@LocalPlayer@@QEAAXAEBUVec2@@@Z
?_applyTurnDelta@LocalPlayer@@QEAAXAEBUVec2@@@Z:
	mov rax, [rel __applyTurnDelta_LocalPlayer__QEAAXAEBUVec2___Z_ptr]
	jmp rax
global ?getSensitivity@Options@@QEBAMW4InputMode@@@Z
?getSensitivity@Options@@QEBAMW4InputMode@@@Z:
	mov rax, [rel _getSensitivity_Options__QEBAMW4InputMode___Z_ptr]
	jmp rax
global ?getCurrentInputMode@IClientInstance@@QEAA?AW4InputMode@@XZ
?getCurrentInputMode@IClientInstance@@QEAA?AW4InputMode@@XZ:
	mov rax, [rel _getCurrentInputMode_IClientInstance__QEAA_AW4InputMode__XZ_ptr]
	jmp rax
