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
;	int		ft_strcmp(const char *s1, const char *s2);

%ifdef __LINUX__
	%define FT_STRCMP ft_strcmp

%else
	%define FT_STRCMP _ft_strcmp
%endif

section .text				; code

global FT_STRCMP			; function name ft_strcmp

FT_STRCMP:
	xor rax, rax			; set rax to 0
	xor rcx, rcx			; set rcx to 0

.loop:
	mov al, byte[rdi]		; get the current *s1 value
	mov cl, byte[rsi]		; get the current *s2 value
	cmp al, 0				; compare *s1 value with '\0'
	jz .return				; if true, turn to _return
	cmp cl, 0				; compare *s2 value with '\0'
	jz .return				; if true, turn to _return
	cmp al, cl				; compare *s2 value with *s1 value
	jne .return				; if false, turn to _return
	inc rdi					; s1++
	inc rsi					; s2++
	jmp .loop				; loop

.return:
	sub rax, rcx			; set the result of *s1 - *s2 to return value
	ret
