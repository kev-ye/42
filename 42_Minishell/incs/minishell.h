/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:07:35 by besellem          #+#    #+#             */
/*   Updated: 2021/06/26 23:24:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////////////////////////////////////////////////////////////
// -- INCLUDES --
////////////////////////////////////////////////////////////////////////////////

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "minishell_defs.h"
# include "ft_termcaps.h"

////////////////////////////////////////////////////////////////////////////////
// -- DATA STRUCTURES --
////////////////////////////////////////////////////////////////////////////////
/*
** Used for the parsing to cut the commands when the following chars are found:
**
** FLG_EO_CMD:			`;'
** FLG_PIPE:			`|'
** FLG_OUTPUT:			`>'
** FLG_APPEND:			`>>'
** FLG_INPUT:			`<'
** FLG_DINPUT:			`<<'
** FLG_EOL:				`\0' (end of line)
** FLG_LRV:				`$?' (code that needs an expansion has been found)
*/
enum	e_flags
{
	FLG_EO_CMD = (1U << 0),
	FLG_PIPE = (1U << 1),
	FLG_OUTPUT = (1U << 2),
	FLG_APPEND = (1U << 3),
	FLG_INPUT = (1U << 4),
	FLG_DINPUT = (1U << 5),
	FLG_EOL = (1U << 6),
	FLG_LRV = (1U << 7)
};

/* Only used whithin a lookup table for the parsing */
struct s_redirections
{
	char		*redir;
	int			len;
	uint16_t	flag;
};

/*
** Used to define the status of the quotes in the parsing:
**
** s_quote:				got a single quote
** d_quote:				got a double quote
** first:				got a quote
** did_change:			did the entry quote has been found again?
**						(so it's the end of a string)
*/
typedef struct s_quotes
{
	int		s_quote;
	int		d_quote;
	int		first;
	int		did_change;
}	t_quotes;

/* Main structure in the parsing to avoid norm errors */
typedef struct s_parsing
{
	t_quotes	quotes;
	t_list		*args;
	int			limit;
	char		*s;
}	t_parsing;

/* Only used whithin a lookup table to execute a command based on key codes */
struct s_termcaps
{
	char	*termcap;
	void	(*f)();
};

/*
** Keeps some important infos about the history:
**
** fd:					fd of the HISTORY_FILENAME created & opened
** current:				current history entry
** size:				size of all the entries
** path:				path of the file
** history:				list containing all entries
*/
typedef struct s_history
{
	int		fd;
	char	*path;
}	t_history;

/*
** Keeps track of the cursor's position:
**
** len:					total len of the current cmd (minus the prompt's len)
** line:				line number
** current_index:		current cursor position on the string
** current_line:		current line number (in case of a small terminal)
*/
typedef struct s_edition
{
	size_t	len;
	size_t	line;
	size_t	current_index;
	size_t	current_line;
}	t_edition;

/*
** Actual commands parsed, almost ready to be executed.
**
** args:				arguments of a command (may be NULL)
** args_len:			len of the arguments of the command
** status_flag:			used with the enum's (e_flags) flags
*/
typedef struct s_cmd
{
	char		**args;
	int			args_len;
	uint16_t	status_flag;
}	t_cmd;

/*
** Used for builtin's execution
**
** cmd:					the command (`cd' for example)
** f1:					a function call with arguments (like `ft_export')
** f2:					a function call without arguments (like `ft_exit')
*/
typedef struct s_builtin
{
	char	*cmd;
	int		(*f1)(t_cmd *cmds);
	int		(*f2)(void);
}	t_builtin;

/*
** Used to handle arguments in the program
**
** opt_c:				is the -c option found (bool)
** fd:					if there's a second arg and it's a file, execute the
						script (the commands actually - nor loop or conditions
						are implemented). Otherwise, set the fd to STDIN_FILENO.
*/
struct s_options
{
	uint8_t	opt_c : 2;
	int		fd;
};

/*
** Main stucture. Called with a singleton.
**
** isatty_stdin:		checks if the STDIN_FILENO fd is a terminal
** last_return_value:	last return value of a command ($?)
** cwd:					pwd (mainly used in the `prompt' function)
** cwd_basename:		only the basename of the current directory
** env:					list of the environment variables
** lst:					main list containing all parsed commands
**						(t_cmd *)(lst->content)
** edit:				struct used for edition
** hist:				struct used for history
** tattr:				terminal's attributes (like the non-canonical mode)
*/
typedef struct s_minishl
{
	int					isatty_stdin;
	int					lrv;
	char				*cwd;
	char				*cwd_basename;
	char				*prompt;
	t_list				*env;
	t_list				*lst;
	t_edition			edit;
	t_history			hist;
	struct s_options	option;
	struct termios		tattr;
	int					rl_lvl;
}	t_minishl;

// cmd utils
typedef struct s_c_init
{
	pid_t	pid;
	int		status;
	int		builtin_status;
	int		input_fd;
	int		output_fd;
	int		lrv;
}	t_c_init;

////////////////////////////////////////////////////////////////////////////////
// -- PROTOTYPES --
////////////////////////////////////////////////////////////////////////////////
/* Utils */
void		*ft_error(char *message, char *file, int line);
int			ft_is_openable(char *path, int flag);
char		*ft_getenv(const char *name);
char		*ft_strnclean(char *s, const char *charset, size_t end);
void		ft_lstprint(t_list *lst, char sep);
void		ft_list_sort(t_list **begin_list, int (*cmp)());
char		**ft_lst2strs(t_list **lst);

/* Memory Management */
void		__ft_free_cmds__(void);
void		ft_free_exit(int code);

/* General */
t_minishl	*singleton(void);
int			ft_init_minishell(char **env);

void		prompt(void);
char		*search_executable(char *command);
t_list		*search_env(char *tofind, t_list **env);

/* General Arguments Handling */
void		option_c(int ac, const char **av);
void		parse_args(int ac, const char **av);

/* Signals */
void		ft_interrupt(int code);

/* Parser */
int			quotes2close(unsigned char c, t_quotes *quotes, int status);
t_cmd		*new_cmd(uint16_t status, t_list **args);
int			__pass_spaces__(t_parsing *p, size_t *i);
int			__check_str_limit__(t_parsing *p, size_t *i);
int			__backslash_case__(t_parsing *p, size_t *i);
int			__handle_quotes__(t_parsing *p, size_t *i);
int			__handle_variable_expansion__(t_parsing *p, size_t *i);
int			__need_to_subdivide_command__(t_parsing *p, size_t *i);
int			__fill_last_command__(t_parsing *p, size_t *i);

void		ft_parse(char *s);

/* Execution */
// General
void		ft_exec_each_cmd(t_list *lst_cmd);
char		*search_executable(char *command);
void		ft_pre_exec_cmd(void *ptr);
int			part_cmd_check(t_list *lst_cmd);
int			syntax_parser(t_list *lst_cmd);
int			builtin_exec(t_cmd *cmds);
int			sys_exec(void *ptr);
int			check_if_path_exist(t_list *env);

// All in one
int			_wstatus(int status);
int			_wifexited(int status);
int			_wexitstatus(int status);
int			_wifsignaled(int status);
int			_wtermsig(int status);
int			check_is_inter(t_list *lst_cmd);
int			check_is_redir_cmd(t_list *lst_cmd);
int			check_have_dinput(t_list *lst_cmd);
int			count_pipe(t_list *lst_cmd);
void		first_cmd(void *cmd, int *fd, t_list *lst_cmd, int pipe_len);
void		interm_cmd(void *cmd, int *fd, int fd_index, t_list *lst_cmd);
void		last_cmd(void *cmd, int *fd, int fd_index, t_list *lst_cmd);
void		redir_parser(t_list *cmd, int *fd_input, int *fd_output);
void		*get_complete_cmd(void *cmd, t_list *lst_cmd);
void		create_fd_output(t_list *cmd);
void		create_fd_input(t_list *cmd);
char		*new_tmp_fd_name(int i);
void		fork_fd(t_list *lst_cmd);
int			check_for_next(t_list *lst_cmd);
char		*get_tmp_fd(int i);
void		simple_cmd(void *cmd);
void		exec_all_in_one(t_list *lst_cmd);
void		set_lrv(int status);
t_c_init	cmd_init(void);
int			builtin_cmd_with_redir(void *cmd, t_list *lst_cmd);
int			builtin_redir_parser(t_list *cmd, int *fd_input, int *fd_output);
void		unlink_all_tmp_fd(int i);

/* Flag */
int			flag_check(t_list *lst_cmd);
int			is_redir(t_list *lst_cmd);
int			is_sep_or_end(t_list *lst_cmd);

/* Builtins */
int			ft_echo(t_cmd *cmds);
int			ft_cd(t_cmd *cmds);
char		*get_old_pwd(void);
int			check_if_oldpwd_exist(t_list *env);
void		replace_pwd(char *old_pwd, char *new_pwd, t_list *env);
void		update_pwd_env(char *old_pwd);
int			ft_pwd(void);
int			ft_env(t_cmd *cmds);
int			ft_export(t_cmd *cmds);
void		add_quote(t_list **lst_env);
char		*head_env(char *env);
int			check_space(char *s);
int			ft_unset(t_cmd *cmds);
void		ft_exit_for_prompt(void);
int			ft_exit(t_cmd *cmds);
int			ft_clear(void);

#endif
