/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:20:39 by besellem          #+#    #+#             */
/*   Updated: 2021/05/19 15:27:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_internal.h"

static char	*convert_p(long long ptr)
{
	char		*data;
	char		*hex;
	long long	div;
	int			i;

	div = 16;
	hex = "0123456789abcdef";
	while (ptr / div >= 16)
		div *= 16;
	data = (char *)malloc(sizeof(char) * (ft_len_base(ptr, 16) + 3));
	if (!data)
		return (NULL);
	i = -1;
	data[++i] = '0';
	data[++i] = 'x';
	while (div > 0)
	{
		data[++i] = hex[ptr / div % 16];
		div /= 16;
	}
	data[++i] = '\0';
	return (data);
}

void	ft_alloc_p(t_data **s, t_indicators t, va_list ap)
{
	char			*data;
	char			*sp;
	unsigned long	tmp;
	unsigned int	len;

	tmp = va_arg(ap, unsigned long);
	data = ft_trns((tmp != 0), convert_p(tmp), ft_strdup("0x"));
	sp = NULL;
	len = ft_trni(t.width >= 0, t.width, t.zero) - (!tmp && t.dot < 0);
	if ((t.dot >= 0 && t.zero >= 0) || t.width >= 0)
		sp = space_padding(data, len);
	if (t.minus == -1)
		add_lstd(s, sp);
	if (data)
		add_lstd(s, data);
	if (!tmp && t.dot < 0)
		add_lstd(s, "0");
	if (t.minus == 1)
		add_lstd(s, sp);
	ft_free(2, sp, data);
}
