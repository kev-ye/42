;	NASM x86_64b
;
;	rax : result register
;	rbx : miscellaneous register
;	rcx : fourth argument register
;	rdx : third argument register
;	rsi : second argument register
;	rdi : first argument register
;	rsp : stack pointer
;	rbp : frame pointer
;
;	|---------------> RAX (16-bit) <-----------------|
;	|                        |--------> EAX <--------|
;	|          63~32         |   31~16   |    15~0   |
;	|                                    |---> AX <--|
;
;	HIGH-------------> AX (16-bit) <---------------LOW
;	|                       |                       |
;	|15|  |  |  |  |  |  | 8| 7|  |  |  |  |  |  | 0|
;	|                       |                       |
;	|---> AH (HH 8-bit) <---|---> AL (LW 8-bit) <---|
;
;
;	size_t ft_strlen(const char *str)

%ifdef __LINUX__
	%define FT_STRLEN ft_strlen

%else
	%define FT_STRLEN _ft_strlen
%endif

section .text			; code

global FT_STRLEN		; function name ft_strlen

FT_STRLEN:
	mov	rax, rdi		; hold the src pointer to tmp_src (rax)

.loop:
	cmp	byte[rax], 0	; compare the *tmp_src value with '\0'
	jz	.return			; if true, turn to _return
	inc	rax				; tmp_src++
	jmp	.loop			; loop

.return:
	sub	rax, rdi		; set the result of src - tmp_src to return value
	ret