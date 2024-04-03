/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:15:12 by kaye              #+#    #+#             */
/*   Updated: 2020/08/17 12:40:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		ft_strlen_plus(int size, char **strs)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
		{
			j++;
			len++;
		}
		i++;
	}
	return (len);
}

char	*ft_malloc_word(int size, char **strs, char *sep)
{
	char	*regroup_str;
	int		len_sep;
	int		len_word;

	len_sep = ft_strlen(sep);
	len_word = ft_strlen_plus(size, strs);
	regroup_str = (char*)malloc(sizeof(char) * len_word +
			(len_sep * size - 1) + 1);
	if (regroup_str == NULL)
		return (NULL);
	return (regroup_str);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*regroup_str;
	int		word;
	int		word_i;
	int		strs_i;
	int		sep_i;

	regroup_str = ft_malloc_word(size, strs, sep);
	word_i = 0;
	word = -1;
	if (size > 0)
	{
		while (++word < size)
		{
			strs_i = 0;
			while (strs[word][strs_i])
				regroup_str[word_i++] = strs[word][strs_i++];
			sep_i = 0;
			while (sep[sep_i] && word < size - 1)
				regroup_str[word_i++] = sep[sep_i++];
		}
	}
	regroup_str[word_i] = '\0';
	return (regroup_str);
}
