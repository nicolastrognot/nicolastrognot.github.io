section .text				;
	global strlen:function		;

strlen:					;
	cmp	rdi, 0h			;
	je	strlen_null		;
	mov	rsi, rdi		;
	mov	rcx, -1			;
strlen_begin:				;
	inc	rcx			;
	cmp	byte [rsi + rcx], 0h	;
	jnz	strlen_begin		;
	mov	rax, rcx		;
	ret				;
strlen_null:				;
	mov	rax, 0h			;
	ret				;
