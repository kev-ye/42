/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 12:09:40 by kaye              #+#    #+#             */
/*   Updated: 2020/08/13 18:25:49 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_power(int nb, int power)
{
	int resultat;
	int i;

	resultat = nb;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	i = 0;
	while (++i < power)
		resultat *= nb;
	return (resultat);
}
