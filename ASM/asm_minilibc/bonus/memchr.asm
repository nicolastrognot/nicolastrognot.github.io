section .text				;
	global	memchr:function		;

memchr:					;
	mov	rcx, -1			;
	cmp	rdi, 0h			;
	je	memchr_null		;
memchr_begin:				;
	inc	rcx			;
	cmp	rdx, rcx		;
	jle	memchr_null		;
	mov	al, byte[rdi + rcx]	;
	cmp	al, sil			;
	je	memchr_return		;
	jmp	memchr_begin		;
memchr_null:				;
	mov	rax, 0h			;
	ret				;
memchr_return:				;
	lea	rax, [rdi + rcx]	;
	ret				;
