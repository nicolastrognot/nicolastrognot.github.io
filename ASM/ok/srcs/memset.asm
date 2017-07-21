section .text				;
	global memset:function		;

memset:					;
	mov	rcx, 0h			;
	cmp	rdi, 0h			;
	je	memset_null		;
memset_begin:				;
	cmp	rdx, rcx		;
	je	memset_end		;
	mov	byte[rdi + rcx], sil	;
	inc	rcx			;
	jmp	memset_begin		;
memset_end:				;
	mov	rax, rdi		;
	ret				;
memset_null:				;
	mov	rax, 0h			;
	ret				;
