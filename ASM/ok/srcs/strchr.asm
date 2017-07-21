section .text				;
	global	strchr:function		;

strchr:					;
	mov	r10, rdi		;
	cmp	r10, 0h			;
	je	strchr_null		;
	mov	r11, rsi		;
	mov	rcx, -1			;
strchr_begin:				;
	inc	rcx			;
	cmp	byte[r10 + rcx], 0h	;
	je	strchr_null		;
	cmp	[r10 + rcx], r11b	;
	je	strchr_return		;
	jmp	strchr_begin		;
strchr_return:				;
	lea	eax, [r10 + rcx]	;
	ret				;
strchr_null:				;
	mov	eax, 0h			;
	ret				;
