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
;	char	*ft_strcpy(char * dst, const char * src);

%ifdef __LINUX__
	%define FT_STRCPY ft_strcpy

%else
	%define FT_STRCPY _ft_strcpy
%endif

section .text				; code

global FT_STRCPY			; function name ft_strcpy

FT_STRCPY:
	mov rax, rdi			; hold the dst pointer to tmp_dst (rax)
	mov rdx, rsi			; hold the src pointer to tmp_src (rdx)

.loop:
	mov cl, byte[rdx]		; get the current *tmp_src value
	cmp cl, 0				; compare the *tmp_src value with '\0'
	jz .return				; if true, turn to _return
	mov byte[rax], cl		; save the *tmp_src value in dst
	inc rax					; tmp_dst++
	inc rdx					; tmp_src++
	jmp .loop				; loop

.return:
	mov byte[rax], 0		; add '\0' at end of the tmp_dst
	mov rax, rdi			; set the first dst pointer to return value
	ret