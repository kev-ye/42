/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:41:44 by kaye              #+#    #+#             */
/*   Updated: 2020/08/12 13:32:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		main(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	j = argc - 1;
	while (j > i)
	{
		ft_putstr(argv[j]);
		write(1, "\n", 1);
		j--;
	}
	return (0);
}
