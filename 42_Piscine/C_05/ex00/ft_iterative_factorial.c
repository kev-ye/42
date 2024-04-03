/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:26:26 by kaye              #+#    #+#             */
/*   Updated: 2020/08/13 15:40:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_factorial(int nb)
{
	int resultat;

	resultat = nb;
	if (nb == 0)
		return (1);
	else if (nb < 0)
		return (0);
	while (--nb != 0)
		resultat *= nb;
	return (resultat);
}
