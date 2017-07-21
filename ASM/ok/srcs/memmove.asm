section .text				;
	global memmove:function		;

memmove:				;
	mov     rcx, 0			;
	cmp	rdi, 0h			;
	je	memmove_null		;
memmove_begin:				;
	cmp     rcx, rdx		;
	je      memmove_reinit		;
	movsx   rax, byte[rsi + rcx]	;
	push	rax			;
	inc	rcx			;
	jmp     memmove_begin           ;
memmove_reinit:                         ;
	mov	rcx, rdx		;
	sub	rcx, 1			;
memmove_middle:				;
	cmp     rcx, 0			;
	jl      memmove_end             ;
	pop	rax			;
	mov	[rdi + rcx], al		;
	sub     rcx, 1			;
	jmp     memmove_middle          ;
memmove_end:				;
	mov	rax, rdi                ;
	ret                             ;
memmove_null:				;
	mov	rax, 0h			;
	ret				;