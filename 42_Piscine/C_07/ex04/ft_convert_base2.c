/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:44:51 by kaye              #+#    #+#             */
/*   Updated: 2020/08/27 16:19:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_is_space(char c);
int		ft_strlen(char *str);
int		ft_check_base(char *base);
int		ft_place_in_base(char nb, char *base);
int		ft_atoi_base(char *str, char *base);

int		ft_len_nbr(int nb, char *base)
{
	int		len_nb;
	int		len_base;

	len_nb = 0;
	len_base = ft_strlen(base);
	while (nb > 0 || nb < 0)
	{
		nb /= len_base;
		len_nb++;
	}
	return (len_nb);
}

char	*ft_putnbr_base(long nb, char *base, int len_base)
{
	char	*stock_nbr;
	long	tmp_nbr;
	int		len_nb;

	tmp_nbr = (nb < 0) ? -nb : nb;
	len_nb = ft_len_nbr(nb, base);
	if (nb > 0)
		stock_nbr = (char*)malloc(sizeof(char) * len_nb + 1);
	else
	{
		stock_nbr = (char*)malloc(sizeof(char) * len_nb + 2);
		len_nb = len_nb + 1;
	}
	if (stock_nbr == NULL)
		return (NULL);
	stock_nbr[len_nb] = '\0';
	while (--len_nb >= 0)
	{
		stock_nbr[len_nb] = base[tmp_nbr % len_base];
		tmp_nbr /= len_base;
	}
	if (nb < 0)
		stock_nbr[0] = '-';
	return (stock_nbr);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*nbr_base_to;
	int		nbr_to_convert;

	if (ft_check_base(base_from) == 0 || ft_check_base(base_to) == 0)
		return (NULL);
	nbr_to_convert = ft_atoi_base(nbr, base_from);
	nbr_base_to = ft_putnbr_base(nbr_to_convert, base_to, ft_strlen(base_to));
	return (nbr_base_to);
}
