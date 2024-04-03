/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:02:24 by besellem          #+#    #+#             */
/*   Updated: 2021/05/09 20:17:39 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_stdlib.h"

static int	in_base(int base, char c)
{
	char	*b;
	int		i;

	b = "0123456789abcdefghijklmnopqrstuvwxyz";
	i = 0;
	while (b[i] && i < base)
	{
		if ((ft_isalpha(b[i]) && ft_isalpha(c)
			&& ft_tolower(b[i]) == ft_tolower(c))
			|| b[i] == c)
		{
			return (i);
		}
		++i;
	}
	return (-1);
}

static int	special_cases(const char *str, int *base)
{
	if ((*base == 0 || *base == 16) && *str && *str == '0' && *(str + 1)
		&& (*(str + 1) == 'x' || *(str + 1) == 'X'))
	{
		*base = 16;
		return (2);
	}
	else if (*base == 0 && *str && *str == '0')
	{
		*base = 8;
		return (1);
	}
	else if (*base == 0)
		*base = 10;
	return (0);
}

static int	get_head(const char *str, int *base, int *min)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		++i;
	*min = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			*min = -1;
	return (i + special_cases(str, base));
}

// #include <stdio.h>
static long	get_ret_val(long nb, int min, int flag)
{
	if (flag == 1)
		return (LONG_MAX);
	else if (flag == -1)
		return (LONG_MIN);
	else
		return (nb * min);
}

// static long	parse_str(const char *str, int min, int base)
// {
// 	long	nb;
// 	int		i;
// 	int		j;
// 	int		flag;

// 	nb = 0;
// 	i = get_head(str, &base, &min);
// 	j = 0;
// 	nb = 0;
// 	flag = 0;
// 	while (str[i + j] && in_base(base, str[i + j]) != -1)
// 	{
// 		if (min == -1)
// 		{
// 			if (nb < 0 || nb * min < (LONG_MIN / base) || (nb == (LONG_MIN / base)))
// 				flag = -1;
// 		}
// 		else
// 		{
// 			if (nb < 0 || nb > (LONG_MAX / base) || (nb == (LONG_MAX / base)))
// 				flag = 1;
// 		}
// 		nb = nb * base + in_base(base, str[i + j++]);
// 	}
// }

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	nb;
	int		min;
	int		i;
	int		j;
	int		flag;

	if (endptr)
		*endptr = (char *)str;
	if (base != 0 && (base < 2 || base > 36))
		return (0);
	i = get_head(str, &base, &min);
	j = 0;
	nb = 0;
	flag = 0;
	while (str[i + j] && in_base(base, str[i + j]) != -1)
	{
		if (min == -1)
		{
			if (nb < 0 || nb * min < (LONG_MIN / base) || (nb == (LONG_MIN / base)))
				flag = -1;
		}
		else
		{
			if (nb < 0 || nb > (LONG_MAX / base) || (nb == (LONG_MAX / base)))
				flag = 1;
		}
		nb = nb * base + in_base(base, str[i + j++]);
		// if (nb > (LONG_MAX / base) && min == 1)
		// 	flag = 1;
		// else if (nb < (LONG_MIN / base))
		// 	flag = -1;
	}
	if (endptr && j)
		*endptr = (char *)(&str[i + j]);
	else if (endptr)
		*endptr = (char *)str;
	return (get_ret_val(nb, min, flag));
}
