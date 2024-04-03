/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:18:05 by kaye              #+#    #+#             */
/*   Updated: 2021/07/20 13:04:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define E_CD_ARG "error: cd: bad arguments\n"
#define E_CD_FAIL "error: cd: cannot change directory to "
#define E_EXEC "error: cannot execute "
#define E_FATAL "error: fatal\n"

#define SUCCESS 0
#define FAILURE 1

#define NO_FLAG 0
#define PIPE 1
#define MULTI 2

typedef struct s_microshell
{
    char    **args;
    char    **env;
    size_t  len;
    int     flag;
}   t_microshell;

t_microshell    microshell;
int             fd[2];

void    _b_zero(void *ptr, size_t size)
{
    while (size)
        ((unsigned char *)ptr)[--size] = 0;
}

void    *_calloc(size_t count, size_t size)
{
    void *ptr;

    ptr = (void *)malloc(count * size);
    if (ptr)
        _b_zero(ptr, count * size);
    return (ptr);
}

size_t    _strlen(char *s)
{
    char *tmp;

    tmp = s;
    while (*tmp)
        ++tmp;
    return (tmp - s);
}

char    *_strdup(char *s)
{
    char *new_s;
    int i;

    if (!s)
        return (NULL);
    i = _strlen(s);
    new_s = _calloc(i + 1, sizeof(char));
    if (!new_s)
        return (NULL);
    i = 0;
    while (s[i])
    {
        new_s[i] = s[i];
        ++i;
    }
    return (new_s);
}

size_t    _agrs_len(char **s)
{
    size_t i;

    i = 0;
    while (s && s[i] != NULL)
    {
        if ((s[i][0] == '|' || s[i][0] == ';') && _strlen(s[i]) == 1)
        {
            if (i == 0)
                i = 1;
            break ;
        }
        ++i;
    }
    return (i);
}

void    _putstr_fd(char *s, int fd)
{
    write(fd, s, _strlen(s));
}

void    _free_args(void)
{
    if (microshell.args)
    {
        for (size_t i = 0; microshell.args[i]; i++)
        {
            free(microshell.args[i]);
            microshell.args[i] = NULL;
        }
        free(microshell.args);
        microshell.args = NULL;
    }
}

void    __msg_print__(char *msg1, char *msg2, int fd)
{
   if (msg1)
        _putstr_fd(msg1, fd);
    if (msg2)
    {
        _putstr_fd(msg2, fd);
        _putstr_fd("\n", fd);
    }
}

void    __exit__(char *msg1, char *msg2, int fd, int ret)
{
    __msg_print__(msg1, msg2, fd);
    _free_args();
    exit(ret);
}

void    _cd(void)
{
    if (microshell.len != 2)
    {
        __msg_print__(E_CD_ARG, NULL, STDERR_FILENO);
        return ;
    }
    if (chdir(microshell.args[1]) == -1)
    {
        __msg_print__(E_CD_FAIL, microshell.args[1], STDERR_FILENO);
        return ;
    }
}

void    _parser(char **av, int i)
{
    int  j;
    int  k;

    _b_zero(&microshell, sizeof(t_microshell));
    microshell.len = _agrs_len(av + i);
    microshell.args = _calloc(microshell.len + 1, sizeof(char *));
    if (!microshell.args)
        __exit__(E_FATAL, NULL, STDERR_FILENO, FAILURE);
    j = i;
    k = 0;
    while (av[j] && (size_t)k < microshell.len)
    {
        microshell.args[k] = _strdup(av[j]);
        if (av[j] && _strlen(av[j]) == 1 && (av[j][0] == ';' || av[j][0] == '|'))
            break ;
        ++k;
        ++j;
    }
    if (av[j] && av[j][0] == '|' && _strlen(av[j]) == 1)
        microshell.flag = PIPE;
    else if (av[j] && av[j][0] == ';' && _strlen(av[j]) == 1)
        microshell.flag = MULTI;
    else
        microshell.flag = NO_FLAG;
}

void    _fork_exec(void)
{
    pid_t pid;

    if (microshell.args[0] && !strcmp(microshell.args[0], "cd"))
        _cd();
    else
    {
        if (microshell.flag == PIPE)
            pipe(fd);
        pid = fork();
        if (pid < 0)
            __exit__(E_FATAL, NULL, STDERR_FILENO, FAILURE);
        else if (pid == 0)
        {
            if (microshell.flag == PIPE)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
            }
            if (execve(microshell.args[0], microshell.args, microshell.env) == -1)
                __exit__(E_EXEC, microshell.args[0], STDERR_FILENO, FAILURE);
        }
        else
        {
            if (microshell.flag == PIPE)
            {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
            }
            waitpid(pid, NULL, 0);
        }
        if (fd[0] != -1)
            close(fd[0]);
    }
}

void    _exec(char **av, char **env)
{
    (void)env;
    size_t  i;

    i = 1;
    while (av[i])
    {
        _parser(av, i);
        microshell.env = env;
        if (!(microshell.args[0] && _strlen(microshell.args[0]) == 1 && microshell.args[0][0] == ';'))
            _fork_exec();
        if (microshell.flag == NO_FLAG || microshell.flag == MULTI)
            i += microshell.len;
        else
            i += microshell.len + 1;
        _free_args();
    }
}

int main(int ac, char **av, char **env)
{
    if (ac <= 1)
        return (0);
    fd[0] = -1;
    fd[1] = -1;
    _exec(av, env);
    return (0);
}