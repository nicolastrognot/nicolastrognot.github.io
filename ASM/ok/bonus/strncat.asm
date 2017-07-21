section .text				;
	global strncat:function		;

strncat:				;
	mov	rcx, 0			;
	mov	r10, rdi		;
	cmp	rsi, 0h			;
	je	strncat_end		;
	cmp	rdi, 0h			;
	jne	strncat_end_s1		;
	mov	r10, rsi		;
	je	strncat_end		;
strncat_end_s1:				;
	cmp	byte[rdi], 0h		;
	je	strncat_begin		;
	inc	rdi			;
	jmp	strncat_end_s1		;
strncat_begin:				;
	cmp	rcx, rdx		;
	je	strcat_set_end		;
	mov	al, byte[rsi]		;
	mov	byte[rdi], al		;
	cmp	byte[rsi], 0h		;
	je	strncat_end		;
	inc	rdi			;
	inc	rsi			;
	inc	rcx			;
	jmp	strncat_begin		;
strcat_set_end:				;
	mov	byte[rdi], 0h		;
strncat_end:				;
	lea	rax, [r10]		;
	ret				;
