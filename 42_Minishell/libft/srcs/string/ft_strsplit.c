/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 15:51:25 by besellem          #+#    #+#             */
/*   Updated: 2021/05/16 02:33:57 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"

static char	**malloc_ptr(const char *str, const char *charset, const size_t len)
{
	char	**s;

	if (!str || !charset)
		return (NULL);
	s = (char **)malloc(sizeof(char *) * (len + 1));
	if (!s)
		return (NULL);
	return (s);
}

static int	is_charset(char c, const char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

static size_t	words_len(const char *str, const char *charset)
{
	char	*ptr;
	size_t	len;

	if (!str || !charset)
		return (0);
	ptr = (char *)str;
	len = 0;
	while (*ptr)
	{
		while (*ptr && is_charset(*ptr, charset))
			++ptr;
		if (*ptr)
			++len;
		while (*ptr && !is_charset(*ptr, charset))
			++ptr;
	}
	return (len);
}

static size_t	w_len(char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_charset(str[i], charset))
		++i;
	return (i);
}

char	**ft_strsplit(const char *str, const char *charset)
{
	const size_t	words = words_len(str, charset);
	size_t			len;
	size_t			i;
	char			*ptr;
	char			**s;

	s = malloc_ptr(str, charset, words);
	if (!s)
		return (NULL);
	i = 0;
	ptr = (char *)str;
	while (*ptr && i < words)
	{
		while (*ptr && is_charset(*ptr, charset))
			++ptr;
		len = w_len(ptr, charset);
		s[i] = ft_calloc(len + 1, sizeof(char));
		if (!s[i])
			return (ft_strsfree(words + 1, s));
		ft_memcpy(s[i++], ptr, len);
		ptr += len;
	}
	s[i] = NULL;
	return (s);
}
