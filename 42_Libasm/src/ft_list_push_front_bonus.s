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
;	void	ft_list_push_front(t_list **begin_list, void *data);

%ifdef __LINUX__
	%define FT_LIST_PUSH_FRONT ft_list_push_front
	%define MALLOC_CALL malloc

%else
	%define FT_LIST_PUSH_FRONT _ft_list_push_front
	%define MALLOC_CALL _malloc
%endif

extern MALLOC_CALL

section .text				; code

global FT_LIST_PUSH_FRONT	; function name ft_list_push_front

FT_LIST_PUSH_FRONT:
	push rbp				; save current stack frame ptr (function beginning)
	mov rbp, rsp			; save current stack ptr in rbp

	push rdi				; push (save) *begin_list value at stack
	push rsi				; push (save) *data value at stack

	mov rdi, 16				; malloc 16 bytes
	call MALLOC_CALL
	pop rsi					; get back *data value from stack
	pop rdi					; get back *bein_list value from stack
	cmp rax, 0				; check if malloc failed
	jz .return
	mov [rax], rsi			; set *data value to *data of new list
	mov r8, [rdi]			; save current ptr (*begin_list) in r8
	mov [rax + 8], r8		; list->next = *begin_list
	mov [rdi], rax			; set the new list ptr to *begin_list

.return:
	mov rsp, rbp			; get back initial stack ptr
	pop rbp					; get back stack frame ptr
	ret