@ Copyright (C) 2015 PSP2SDK Project
@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at http://mozilla.org/MPL/2.0/.

.macro PSP2_EXPORT_START
	.section .sceExport.rodata, "a", %progbits
	.subsection 1
	.align	2
.NIDTBL_TOP:

	.subsection 2
	.align	2
.ENTTBL_TOP:
.endm

.macro PSP2_EXPORT_FUNC_START
	.section .sceExport.rodata
	.subsection 1
	.align	2
.NIDTBL_FUNC_TOP:
.endm

.macro PSP2_EXPORT_FUNC nid, func
	.section .sceExport.rodata
	.subsection 1
	.word	\nid

	.subsection 2
	.word	\func
.endm

.macro PSP2_EXPORT_FUNC_END
	.section .sceExport.rodata
	.subsection 1
.NIDTBL_FUNC_BTM:
.endm

.macro PSP2_EXPORT_VAR_START
	.section .sceExport.rodata
	.subsection 1
	.align	2
.NIDTBL_VAR_TOP:
.endm

.macro PSP2_EXPORT_VAR nid, var
	.section .sceExport.rodata
	.subsection 1
	.word	\nid

	.subsection 2
	.word	\var
.endm

.macro PSP2_EXPORT_VAR_END
	.section .sceExport.rodata
	.subsection 1
.NIDTBL_VAR_BTM:
.endm

.macro PSP2_EXPORT_END ver, flag, nid, name
	.section .sceLib.ent, "a", %progbits
	.align	2
	.short	0x0020
	.short	\ver
	.short	\flag
.ifdef .NIDTBL_FUNC_TOP
	.short	(.NIDTBL_FUNC_BTM - .NIDTBL_FUNC_TOP) / 4
.else
	.short	0
.endif
.ifdef .NIDTBL_VAR_TOP
	.word	(.NIDTBL_VAR_BTM - .NIDTBL_VAR_TOP) / 4
.else
	.word	0
.endif
	.word	0
	.word	\nid
	.word	.STR
	.word	.NIDTBL_TOP
	.word	.ENTTBL_TOP

	.section .sceExport.rodata
.STR:
	.asciz	"\name"
.endm
