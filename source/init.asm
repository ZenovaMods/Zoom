; This file was automatically generated using tools/process_csv.py
; Generated on Fri Jul 17 2020 17:56:31 UTC
bits 64
SECTION .data
extern _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr
extern __RCameraPairHasher__QEAA_KAEBU_$pair_VHashedString__V1__std___Z_ptr

SECTION .text
global ?getFov@LevelRendererPlayer@@QEAAMM_N@Z
?getFov@LevelRendererPlayer@@QEAAMM_N@Z:
	mov rax, [rel _getFov_LevelRendererPlayer__QEAAMM_N_Z_ptr]
	jmp rax
global ??RCameraPairHasher@@QEAA_KAEBU?$pair@VHashedString@@V1@@std@@@Z
??RCameraPairHasher@@QEAA_KAEBU?$pair@VHashedString@@V1@@std@@@Z:
	mov rax, [rel __RCameraPairHasher__QEAA_KAEBU_$pair_VHashedString__V1__std___Z_ptr]
	jmp rax
