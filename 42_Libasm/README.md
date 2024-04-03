# 42 project : Libasm

## __Index__

* [Presentation](#Presentation)
* [To do list](#To_do_list)
* [Register](#Register)
* [Syscall](#Syscall)
* [NASM command](#NASM_command)

## Presentation

The aim of this project is to get familiar with assembly language.

## To_do_list

- [x] ft_strlen
- [x] ft_strcpy
- [x] ft_strcmp
- [x] ft_write
- [x] ft_read
- [x] ft_strdup

## __Register__
[__Original__](https://www.codenong.com/cs109851814/)

* [Memory Data Register](#Memory_Data_Register) : AX, BX, CX, DX  
	* [High H & low L](#High_H_and_low_L) : AH, BH, CH, DH & AL, BL, CL, DL  
	* [32bit & 64bit](#32bit_and_64bit) : EAX, EBX, ECX, EDX & RAX, RBX, RCX, RDX  
* [Segment Register](#Segment_Register) : CS, DS, SS, ES, FS ,GS
* [Pointer Register](#Pointer_Register) : IP, SP, BP
	* 32bit : EIP, ESP, EBP
* [Index Registrer](Index_Registrer) : SI, DI
* [Control register](Control_register) : IP, FLAGS

### Memory_Data_Register

	Data storage. Common registers are AX, BX, CX, DX

>AX (Accumlator)
>>Used in input/output and most arithmetic instructions

>BX (Base)
>>Used in index addressing

>CX (Counter)
>>Used to loop count iteration operations

>DX (Data)
>>Used for input/output operations

#### High_H_and_low_L
	The four 16-bit registers can be split in to high 8-bits and low 8-bits, namely AH, BH, CH and AL, BL, CL, DL.
	
	these 8 registers are not new registers, but take part of the contents of the corresponding 16-bit registers. Take the actual storage situation of AX as an example.

	HIGH-------------> AX (16-bit) <---------------LOW
	|                       |                       |
	|15|  |  |  |  |  |  | 8| 7|  |  |  |  |  |  | 0|
	|                       |                       |
	|---> AH (HH 8-bit) <---|---> AL (LW 8-bit) <---|

#### 32bit_and_64bit
	At the same time, NASM also supports us to write 32-bit or 64-bit general register size, which are EAX, EBX, ECX, EDX and RAX, RBX, RCX, RDX.

	For example, the original AX is the lower 16-bit of EAX as follows.

	|---------------> RAX (16-bit) <-----------------|
	|                        |--------> EAX <--------|
	|          63~32         |   31~16   |    15~0   |
	|                                    |---> AX <--|

### Segment_Register
	the second one we will introduce the segment registerm because manyu other registers needs to be used together with the segment register. There are 4+2 types of segment registers defined by NASM (the latter two are more after 80386, providing more choices).

>CS (Code)
>>Used to save the starting address of the code segment of the currently executing program, which is equivalent to the address of section .text

>DS (Data)
>>Used to save the starting address of the data segment of the currently executing program, which is equivalent to the address of section .data

>SS (Stack)
>>Used to save the base address of the current stack space (Stack), add SP (offset) -> SS:SP to find the current stack top address

>ES (Extra)
>>Memory addressing base address commonly used for string operations, shared with index register DI

>FS, GS
>>80386 additional defined segment registers, providing programmers more options for segment addresses

### Pointer_Register
	With the previous segment register storing different sections (section or segment segment), we also have three registers as pointers in the block (used to store the offset offset)

>IP (Instruction Pointer)
>>Shared with CS, the address of the current program can be found through CS:IP

>SP (Stack Pointer)
>>Shared with SS, the current stack top address can be found through SS:SP

>BP (Base Pointer)
>>Shared with SS, the current stack bottom address can be found through SS:BP

The addressing of the pointer register is as follows:

	                           memory address allocation
	         High address|------------------------------------|
	                     |------------------------------------|
	                     |                                    |
	Current prog place-->|            Code Segment            |
	                  ↑IP|                                    |
	               CS -->|------------------------------------|
	                     |                                    |
	                     |            Data Segment            |
	                     |                                    |
	            DS, SS-->|------------------------------------|
	                  ↓SP|                                    ||stack addr
	        Stack head-->|               Stack                ||incease from
	                     |                                    ||high to
	                     |------------------------------------|↓bottom
	          Low address|------------------------------------|

### Index Registrer
	Due to the limited registers, sometimes we do not directly save the operand or the address of the operand, but save a relative offset of the operand, and manipulate the data through indirect addressing. The index register is the part responsible for saving the offset in this process

>SI (Source Index)
>>Usually used to save the offset of the source operand (string), used with DS (DS:SI)

>DI (Destination Index)
>>Usually used to save the offset of the destination operand (string), used with ES (ES:DI)

### Control register
	In fact, IP can be regarded as a kind of control register, which determines the offset of the instruction fetch when the program is executed, but since it is still an offset, it is introduced here in the part of the pointer register.

The control register FLAGS saves the status of CPU operation and some flag bits, each bit represents a different meaning:

	| 15 | 14 | 13 | 12 | 11 | 10 |  9 |  8 |  7 |  6 |  5 |  4 |  3 |  2 |  1 | 0  |
	|    |    |    |    | OF | DF | IF | TF | SF | ZF |    | AF |    | PF |    | CF |
	|    |    |    |    |OVER|DIRE|INTE|TRAP|SIGN|ZERO|    |ADJU|    |PARI|    |CARR|
	|    |    |    |    |FLOW|CTIO|RRUP|    |    |    |    |ST  |    |TY  |    |Y   |
	|    |    |    |    |    |N   |T   |    |    |    |    |    |    |    |    |    |

>0th Carry flag
>>Set to 1 when there is a carry or borrow

>2nd Party flag 
>>Set to 1 if an arithmetic operation contains an even number of 1

>4th Adjust flag
>>Carry flag in low four-bit operation

>6th Zero flag
>>Set to 1 when the operation result is 0

>7th Sign flag
>>Set to 1 when the result of the operation is negative, the same as the highest bit of the result

>8th Trap flag
>>set to 1 means single-step debugging, execute one instruction at a time

>9th Interrupt enable flag
>>Set to 1 when it can respond to external interrupts

>10 Direction flag
>>When set to 0, SI and DI decrement every time the serial instruction operates

>11th Overflow flag
>>Set to 1 when the operation result overflows

## __Syscall__

__Macos XNU (BSD / MACH) :__

	syscall.h :

	SYS_syscall	: 0
	SYS_exit	: 1
	SYS_fork	: 2
	SYS_read	: 3
	SYS_write	: 4
	SYS_open	: 5
	SYS_close	: 6
	SYS_wait4	: 7
	...

	Add 0x2000000 (Example : SYS_exit -> 0x2000001).

__Linux 64-bit :__  
[__More_info__](https://filippo.io/linux-syscall-table/)

	syscall.h :

	SYS_exit	: 60
	SYS_fork	: 57
	SYS_read	: 0
	SYS_write	: 1
	SYS_open	: 2
	SYS_close	: 3
	SYS_wait4	: 61
	...


## __NASM_command__
	There is currently no content ...