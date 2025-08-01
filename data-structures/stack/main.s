	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 4
	.globl	_initialize                     ; -- Begin function initialize
	.p2align	2
_initialize:                            ; @initialize
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x9, [sp, #8]
	mov	w8, #-1
	str	w8, [x9, #400]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_is_full                        ; -- Begin function is_full
	.p2align	2
_is_full:                               ; @is_full
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	ldr	w8, [x8, #400]
	subs	w8, w8, #99
	cset	w8, ge
	and	w0, w8, #0x1
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_is_empty                       ; -- Begin function is_empty
	.p2align	2
_is_empty:                              ; @is_empty
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	ldr	w8, [x8, #400]
	adds	w8, w8, #1
	cset	w8, eq
	and	w0, w8, #0x1
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_push                           ; -- Begin function push
	.p2align	2
_push:                                  ; @push
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	ldur	x0, [x29, #-8]
	bl	_is_full
	tbz	w0, #0, LBB3_2
	b	LBB3_1
LBB3_1:
	mov	x9, sp
	mov	x8, #100
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	b	LBB3_3
LBB3_2:
	ldur	w8, [x29, #-12]
	ldur	x9, [x29, #-8]
	ldur	x11, [x29, #-8]
	ldr	w10, [x11, #400]
	add	w10, w10, #1
	str	w10, [x11, #400]
	str	w8, [x9, w10, sxtw #2]
	b	LBB3_3
LBB3_3:
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_pop                            ; -- Begin function pop
	.p2align	2
_pop:                                   ; @pop
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #16]
	ldr	x0, [sp, #16]
	bl	_is_empty
	tbz	w0, #0, LBB4_2
	b	LBB4_1
LBB4_1:
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	mov	w8, #-1
	stur	w8, [x29, #-4]
	b	LBB4_3
LBB4_2:
	ldr	x8, [sp, #16]
	ldr	x9, [sp, #16]
	ldrsw	x9, [x9, #400]
	ldr	w8, [x8, x9, lsl #2]
	str	w8, [sp, #12]
	ldr	x9, [sp, #16]
	ldr	w8, [x9, #400]
	subs	w8, w8, #1
	str	w8, [x9, #400]
	ldr	w8, [sp, #12]
	stur	w8, [x29, #-4]
	b	LBB4_3
LBB4_3:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_peek                           ; -- Begin function peek
	.p2align	2
_peek:                                  ; @peek
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp]
	ldr	x0, [sp]
	bl	_is_empty
	tbz	w0, #0, LBB5_2
	b	LBB5_1
LBB5_1:
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	mov	w8, #-1
	stur	w8, [x29, #-4]
	b	LBB5_3
LBB5_2:
	ldr	x8, [sp]
	ldr	x9, [sp]
	ldrsw	x9, [x9, #400]
	ldr	w8, [x8, x9, lsl #2]
	stur	w8, [x29, #-4]
	b	LBB5_3
LBB5_3:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #480
	.cfi_def_cfa_offset 480
	stp	x28, x27, [sp, #448]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #464]            ; 16-byte Folded Spill
	add	x29, sp, #464
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	stur	wzr, [x29, #-20]
	add	x0, sp, #40
	str	x0, [sp, #24]                   ; 8-byte Folded Spill
	bl	_initialize
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	mov	w1, #3
	bl	_push
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	bl	_peek
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x0
	str	x8, [x9]
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	str	x0, [sp, #32]                   ; 8-byte Folded Spill
	bl	_printf
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	mov	w1, #5
	bl	_push
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	bl	_peek
	mov	x10, x0
	ldr	x0, [sp, #32]                   ; 8-byte Folded Reload
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	bl	_printf
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	mov	w1, #2
	bl	_push
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	bl	_peek
	mov	x10, x0
	ldr	x0, [sp, #32]                   ; 8-byte Folded Reload
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	bl	_printf
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	mov	w1, #8
	bl	_push
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	bl	_peek
	mov	x10, x0
	ldr	x0, [sp, #32]                   ; 8-byte Folded Reload
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	bl	_printf
	b	LBB6_1
LBB6_1:                                 ; =>This Inner Loop Header: Depth=1
	add	x0, sp, #40
	bl	_is_empty
	tbnz	w0, #0, LBB6_3
	b	LBB6_2
LBB6_2:                                 ;   in Loop: Header=BB6_1 Depth=1
	add	x0, sp, #40
	str	x0, [sp, #16]                   ; 8-byte Folded Spill
	bl	_peek
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x0
	str	x8, [x9]
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	bl	_printf
	ldr	x0, [sp, #16]                   ; 8-byte Folded Reload
	bl	_pop
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x0
	str	x8, [x9]
	adrp	x0, l_.str.4@PAGE
	add	x0, x0, l_.str.4@PAGEOFF
	bl	_printf
	b	LBB6_1
LBB6_3:
	mov	w0, #0
	ldp	x29, x30, [sp, #464]            ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #448]            ; 16-byte Folded Reload
	add	sp, sp, #480
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Stack Overflow, max size exceeded: %d !\n"

l_.str.1:                               ; @.str.1
	.asciz	"Stack Underflow, the stack is empty!\n"

l_.str.2:                               ; @.str.2
	.asciz	"Stack is empty\n"

l_.str.3:                               ; @.str.3
	.asciz	"Top element: %d\n"

l_.str.4:                               ; @.str.4
	.asciz	"Popped element: %d\n"

.subsections_via_symbols
