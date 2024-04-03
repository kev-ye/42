# Libft
First project @42Paris recreating libc functions in C language.
Various functions were added after validating the project (there are even some that may not exist in the real libc).

## The library
It contains most of the functions of the following header files from the libc:</br>
`ctype.h`</br>
`math.h`</br>
`printf.h`</br>
`stdint.h`</br>
`stdio.h`</br>
`stdlib.h`</br>
`string.h`</br>

Adding some custom functions and header too as, for example:</br>
`ansi_codes.h` adding some of the ANSI color and clearing codes</br>
`defs.h` adding special defines for the lib</br>
`ft_list.h` adding list functions</br>
`get_next_line.h` adding [get_next_line](https://github.com/besellem/get_next_line) function, reading a file descriptor line by line</br>

Feel free to check out the actual prototypes and code of the functions !

## Compilation / use
Compile the lib with a simple `make` command.
You can then add `#include <libft.h>` in your project and compile with the flags `-Ilibft/incs -Llibft -lft` (assuming that you are in the parent directory).
