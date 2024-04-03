/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 11:49:45 by kaye              #+#    #+#             */
/*   Updated: 2020/08/06 11:58:49 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_ultimate_div_mod(int *a, int *b)
{
	int resultatdiv;
	int resultatmod;

	resultatdiv = *a / *b;
	resultatmod = *a % *b;
	*a = resultatdiv;
	*b = resultatmod;
}
