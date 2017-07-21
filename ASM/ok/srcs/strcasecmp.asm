section .text				;
	global strcasecmp:function	;

strcasecmp:				;
	mov	rcx, -1			;
	mov	r11, rsi		;
	mov	r10, rdi		;
	cmp	rdi, 0h			;
	je	strcasecmp_null_1	;
	cmp	rsi, 0h			;
	je	strcasecmp_null_1_passed;
strcasecmp_begin:			;
	inc	rcx			;
	cmp	byte[rdi + rcx], 0h	;
	je	strcasecmp_value	;
	cmp	byte[rsi + rcx], 0h	;
	je	strcasecmp_value	;
	mov	r10b, byte[rdi + rcx]	;
	mov	r11b, byte[rsi + rcx]	;
	cmp	byte[rdi + rcx], 'A'	;
	jl	strcasecmp_endif	;
	cmp	byte[rdi + rcx], 'Z'	;
	jg	strcasecmp_endif	;
	or	r10b, 20h		;
strcasecmp_endif:			;
	cmp	byte[rsi + rcx], 'A'	;
	jl	strcasecmp_endif2	;
	cmp	byte[rsi + rcx], 'Z'	;
	jg	strcasecmp_endif2	;
	or	r11b, 20h		;
strcasecmp_endif2:			;
	cmp	r10b, r11b		;
	jne	strcasecmp_value	;
	jmp	strcasecmp_begin	;
strcasecmp_value:			;
	movsx	eax, r10b		;
	movsx	edx, r11b		;
	jmp	strcasecmp_return	;
strcasecmp_null_1:			;
	mov	eax, 0h			;
	cmp	rsi, 0h			;
	je	strcasecmp_null_2	;
	movsx	edx, byte[rsi]		;
	jmp	strcasecmp_return	;
strcasecmp_null_1_passed:		;
	movsx	eax, byte[rdi]		;
strcasecmp_null_2:			;
	mov	edx, 0h			;
strcasecmp_return:			;
	sub	eax, edx		;
	ret				;
