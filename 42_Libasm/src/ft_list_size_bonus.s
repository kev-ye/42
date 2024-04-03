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
;	int	ft_list_size(t_list *begin_list);

%ifdef __LINUX__
	%define FT_LIST_SIZE ft_list_size

%else
	%define FT_LIST_SIZE _ft_list_size
%endif

section .text			; code

global FT_LIST_SIZE		; function name ft_list_size

FT_LIST_SIZE:
	xor rax, rax

.loop:
	cmp rdi, 0
	jz .return
	mov rdi, [rdi + 8]
	inc rax
	jmp .loop

.return:
	ret