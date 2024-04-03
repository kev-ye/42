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
; ssize_t	ft_read(int fildes, void *buf, size_t nbyte);

%ifdef __LINUX__
	%define FT_READ ft_read
	%define SYS_CALL_READ_NUM 0x0
	%define ERRNO_CALL __errno_location

%else
	%define FT_READ _ft_read
	%define SYS_CALL_READ_NUM 0x2000003
	%define ERRNO_CALL ___error
%endif

extern ERRNO_CALL					; include errno

section .text						; code

global FT_READ						; function name ft_read

FT_READ:
	mov	rax, SYS_CALL_READ_NUM
    syscall
    %ifdef __LINUX__
		cmp rax, 0
		jl .errno					; in linux, the error value return on syscall is negative
	%else
		jc .errno					; in macos, the error value return on syscall is positive but it will activate CFLAG
    %endif
	ret

.errno:
	%ifdef __LINUX__
		neg rax						; errno is postive value, so we turn it to positive
	%endif
	mov r10, rax					; save the errno value to r10 (a free register)
	call ERRNO_CALL					; call errno, get result in rax register
	mov qword[rax], r10				; put the errno value in rax register
	mov rax, -1						; set -1 as the return value
	ret