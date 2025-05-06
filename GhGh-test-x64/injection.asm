EXTERN enterFunction : PROC
EXTERN exitFunction : PROC

.code

PUBLIC _penter
PUBLIC _pexit

PUSHREGS	macro
	push	rax
	lahf
	push	rax
	push	rcx
	push	rdx
	push	r8
endm

POPREGS	macro
	pop	r8
	pop	rdx
	pop	rcx
	pop	rax
	sahf
	pop	rax
endm

_penter	proc
	PUSHREGS

	mov	rcx, rsp
	mov	rdx, qword ptr [rsp + 28h]
	call enterFunction

	POPREGS
	ret
_penter	endp

_pexit	proc
	PUSHREGS

	call exitFunction

	POPREGS
	ret
_pexit	endp

END