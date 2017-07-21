section .text				;
	global	strcmp:function		;

strcmp:					;
	mov	rcx, -1			;
	cmp	rdi, 0h			;
	je	strcmp_null_1		;
	cmp	rsi, 0h			;
	je	strcmp_null_1_passed	;
strcmp_begin:				;
	inc	rcx			;
	cmp	byte[rsi + rcx], 0h	;
	je	strcmp_value		;
	cmp	byte[rdi + rcx], 0h	;
	je	strcmp_value		;
	mov	al, byte[rsi + rcx]	;
	cmp	al, byte[rdi + rcx]	;
	jne	strcmp_value		;
	jmp	strcmp_begin		;
strcmp_value:				;
	movsx	eax, byte[rdi + rcx]	;
	movsx	edx, byte[rsi + rcx]	;
	jmp	strcmp_return		;
strcmp_null_1:				;
	mov	eax, 0h			;
	cmp	rsi, 0h			;
	je	strcmp_null_2		;
	movsx	edx, byte[rsi]		;
	jmp	strcmp_return		;
strcmp_null_1_passed:			;
	movsx	eax, byte[rdi]		;
strcmp_null_2:				;
	mov	edx, 0h			;
strcmp_return:				;
	sub	eax, edx		;
	ret				;
