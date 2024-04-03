/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ip_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:19:42 by kaye              #+#    #+#             */
/*   Updated: 2020/12/07 01:42:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	    *ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = strlen(s1) + strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	memmove(str, s1, strlen(s1));
	memmove(str + strlen(s1), s2, strlen(s2));
	str[len] = '\0';
	return (str);
}

static size_t	ft_intlen_base(int n, int base)
{
	size_t count;

	count = (n) ? 0 : 1;
	while (n)
	{
		n = n / base;
		++count;
	}
	return (count);
}

static int		ft_conv_dh_itoa(int n)
{
	if (n < 10)
		return (n + '0');
	else
		return (n - 10 + 'a');
}

static char			*ft_itoa_base(int n, int base)
{
	size_t			len;
	char			*str;
	unsigned int	n_tmp;
	size_t			t_len;

	n_tmp = (n < 0) ? -(unsigned int)n : n;
	len = (n < 0) ? ft_intlen_base(n_tmp, base) + 1 :
					ft_intlen_base(n_tmp, base);
	t_len = len;
	if (len < 8)
		len = 8;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[t_len] = '\0';
	str[len] = '\0';
	while (t_len--)
	{
		str[t_len] = ft_conv_dh_itoa(n_tmp % base);
		n_tmp /= base;
	}
	if (n < 0)
		str[0] = '-';
	--len;
	while (str[len] != '1' && str[len] != '0')
	{
		str[len] = '0';
		--len;
	}
	return (str);
}

long get_ip_number(int mask1, int mask2, int mask3, int mask4)
{
    long result;
    int count;
    int i;
    char *str1;
    char *str2;
    char *str3;
    char *mk1 = ft_itoa_base(mask1, 2);
    char *mk2 = ft_itoa_base(mask2, 2);
    char *mk3 = ft_itoa_base(mask3, 2);
    char *mk4 = ft_itoa_base(mask4, 2);
    
    str1 = ft_strjoin(mk1, mk2);
    str2 = ft_strjoin(str1, mk3);
    str3 = ft_strjoin(str2, mk4);
    
    free(mk1);
    free(mk2);
    free(mk3);
    free(mk4);
    free(str1);
    free(str2);
    
    i = 0;
    count = 0;
    while (str3[i])
    {
        if (str3[i] == '0')
            ++count;
        i++;
    }
    free(str3);
    result = 1;
    while(count > 0)
    {
        result = result * 2;
        --count;
    }
    return (result - 2);
}