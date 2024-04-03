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
;	r9	; fifth argument register
;	r9	; sixth argument register
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
;	char	*ft_strdup(const char *s1);

%ifdef __LINUX__
	%define FT_STRDUP ft_strdup
	%define FT_STRLEN ft_strlen
	%define FT_STRCPY ft_strcpy
	%define MALLOC_CALL malloc

%else
	%define FT_STRDUP _ft_strdup
	%define FT_STRLEN _ft_strlen
	%define FT_STRCPY _ft_strcpy
	%define MALLOC_CALL _malloc
%endif

extern FT_STRLEN
extern FT_STRCPY
extern MALLOC_CALL

section .text			; code

global FT_STRDUP		; function name ft_strdup

FT_STRDUP:
	push rdi			; push (save) s1 value to stack

.cpy:
	call FT_STRLEN		; rdi already has str value
	add rax, 1			; add 1 to length
	mov rdi, rax		; set length value to 1st arg (parameter of malloc)
	call MALLOC_CALL
	cmp rax, 0			; check if malloc failed
	jz .return
	mov rdi, rax		; set malloc addr to dst register
	pop rsi				; set src value from stack
	call FT_STRCPY
	ret					; return the malloc string

.return:
	ret					; if malloc failed, return NULL