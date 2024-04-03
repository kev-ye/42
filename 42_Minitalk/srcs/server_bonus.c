/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:45:53 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 13:20:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_mtlk
{
	int		c;
	int		i;
	int		len;
	int		max;
	int		progress;
	char	*str;
}	t_mtlk;

static void	print_len(t_mtlk *mtlk)
{
	if (mtlk->len == 0)
	{
		ft_putstr(B_GREEN"--- String length: [");
		ft_putnbr(mtlk->c);
		ft_putstr("] ---\n"NONE);
		mtlk->max = mtlk->c;
		mtlk->len = 32;
		mtlk->i = 8;
		mtlk->c = 0;
	}
}

static void	print_end(t_mtlk *mtlk)
{
	if (mtlk->progress == mtlk->max)
	{
		load_bar(mtlk->progress, mtlk->max);
		ft_putchar('\n');
		mtlk->len = 31;
		mtlk->i = 7;
		mtlk->c = 0;
		mtlk->max = -1;
		mtlk->progress = 0;
		ft_putstr(B_YELLOW"-> Content : ["NONE);
		if (mtlk->str)
		{
			ft_putstr(mtlk->str);
			free(mtlk->str);
			mtlk->str = NULL;
		}
		ft_putstr(B_YELLOW"] <-\n"NONE);
		ft_putstr(B_GREEN"--- END OF STRING ! ---\n"NONE);
	}
}

static void	print_str(int opt)
{
	static t_mtlk	mtlk = {.c = 0, .i = 7,
		.len = 31, .max = -1, .progress = 0, .str = NULL};

	if (opt == SIGUSR1 && mtlk.len != 32)
		mtlk.c = mtlk.c | (1 << mtlk.len);
	else if (opt == SIGUSR1 && mtlk.len == 32)
		mtlk.c = mtlk.c | (1 << mtlk.i);
	print_len(&mtlk);
	if (mtlk.i == 0)
	{
		mtlk.str = add_c2str(mtlk.str, mtlk.c);
		load_bar(mtlk.progress, mtlk.max);
		mtlk.i = 8;
		mtlk.c = 0;
		++mtlk.progress;
	}
	if (mtlk.len != 32)
		--mtlk.len;
	if (mtlk.len == 32)
		--mtlk.i;
	print_end(&mtlk);
}

static void	ft_handle(int code)
{
	if (code == SIGUSR1)
		print_str(SIGUSR1);
	else
		print_str(SIGUSR2);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr("PID : ["B_CYAN);
	ft_putnbr(pid);
	ft_putstr(NONE"]\n");
	while (1)
	{
		signal(SIGUSR1, ft_handle);
		signal(SIGUSR2, ft_handle);
		pause();
	}
	return (SUCCESS);
}
