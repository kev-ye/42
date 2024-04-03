/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:31:30 by besellem          #+#    #+#             */
/*   Updated: 2021/06/24 18:33:50 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFS_H
# define MINISHELL_DEFS_H

/* Prompt string */
# define PROG_NAME "minishell"

# define PROMPT "\e[1;36m\e[1m%s \e[1;31m$ \e[0m"

/* History file. May be renamed at compile time */
# ifndef HISTORY_FILENAME
#  define HISTORY_FILENAME ".minishell_history"
# endif

/* tmp file used for '<<' */
# define TMP_FD "./double_input_fd"

/* Error messages */
# define ERR_MALLOC "malloc error"
# define ERR_OPEN   "cannot open file"
# define SYNTAXERR  "syntax error near unexpected token"

/*
** Some simple & useful macros
*/
# define SUCCESS    0
# define ERROR      1

# define FOUND      0
# define NOT_FOUND  (-1)

# ifndef TRUE
#  define TRUE      1
# endif
# if defined(TRUE) && 1 != TRUE		/* May be set already */
#  undef TRUE
#  define TRUE      1
# endif

# ifndef FALSE
#  define FALSE     0
# endif
# if defined(FALSE) && 0 != FALSE	/* May be set already */
#  undef FALSE
#  define FALSE     0
# endif

/*
** Various codes
*/
/* Exec */
# define SIMPLE     0
# define ONLY_PIPE  1
# define ONLY_REDIR 2
# define MIX        4
# define NO_OPTION  0
# define PIPE_OPEN  1
# define REDIR_OPEN 2
# define NO_FIRST   0
# define FIRST      1

/* fd flags */
# define F_APPEND   1
# define F_TRUNC    2
# define F_INPUT    3
# define F_DINPUT   4

/* Redir parser */
# define RET_INIT   0
# define CTRLD      1
# define OUTPUT     2

/* Check */
# define NO_ONE     (-1)

/* Bultin */
# if defined(__APPLE__) && defined(__MACH__)
#  define NO_NUM_ARG 255
# else
#  define NO_NUM_ARG 2
# endif

/* LRV -> Last Return Value ($?) */
# define PID_FAILURE       1
# define EXEC_FAILURE      1
# define LRV_SYNTAX_ERROR  258
# define LRV_PERMISSION    126
# define LRV_CMD_NOT_FOUND 127
# define LRV_GENERAL_ERROR 1
# define LRV_KILL_SIG      128
# define LRV_REPLACEMENT   (-1) /* before the ascii table */

/* used to reset static variables in `quotes2close' */
# define QUOTES_RESET_FLAG 1

/* used to set static variables normally in `quotes2close' */
# define QUOTES_SET_FLAG   0

/* Charsets used in the parsing */
# define SPACES      " \t"
# define QUOTES      "\"'"
# define SPEC_CHARS  "\\$'\"" /* Special chars n1 */
# define SPEC_CHARS2 "\\$\""  /* Special chars for `\' in double quotes */

#endif
