/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 17:17:51 by kaye              #+#    #+#             */
/*   Updated: 2020/08/25 19:47:52 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_do_op.h"

int		ft_do_op(int nb1, int nb2, int (*f)(int, int))
{
	int resultat;

	resultat = (f)(nb1, nb2);
	return (resultat);
}

int		ft_do_op_sal(int nb1, int nb2, int op)
{
	int resultat;

	resultat = 0;
	if (op == '+')
		resultat = ft_do_op(nb1, nb2, &ft_addition);
	else if (op == '-')
		resultat = ft_do_op(nb1, nb2, &ft_soustraction);
	else if (op == '*')
		resultat = ft_do_op(nb1, nb2, &ft_multiplication);
	else if (op == '/')
		resultat = ft_do_op(nb1, nb2, &ft_division);
	else if (op == '%')
		resultat = ft_do_op(nb1, nb2, &ft_modulo);
	return (resultat);
}

int		main(int ac, char **av)
{
	char	*nb1;
	char	*nb2;
	int		resultat;

	resultat = 0;
	nb1 = av[1];
	nb2 = av[3];
	if (ac == 4)
	{
		if (ft_strlen(av[2]) < 2 && av[2][0] == '/' && av[3][0] == '0')
		{
			ft_putstr("Stop : division by zero\n");
			return (0);
		}
		else if (ft_strlen(av[2]) < 2 && av[2][0] == '%' && av[3][0] == '0')
		{
			ft_putstr("Stop : modulo by zero\n");
			return (0);
		}
		if (ft_strlen(av[2]) < 2)
			resultat = ft_do_op_sal(ft_atoi(nb1), ft_atoi(nb2), av[2][0]);
		ft_putnbr(resultat);
		ft_putchar('\n');
	}
	return (0);
}
