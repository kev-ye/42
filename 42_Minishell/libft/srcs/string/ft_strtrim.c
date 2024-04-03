/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 21:53:35 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 14:40:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static unsigned int	is_set(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static unsigned int	head_index(char const *str, char const *set)
{
	unsigned int	i;

	i = 0;
	while (str[i] && is_set(str[i], set))
		++i;
	return (i);
}

static unsigned int	tail_index(char const *str, char const *set)
{
	unsigned int	i;

	i = ft_strlen(str);
	while (i-- > 0)
		if (!is_set(str[i], set))
			return (i);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*new;
	unsigned int	head;
	unsigned int	tail;
	unsigned int	i;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	head = head_index(s1, set);
	if (!s1[head])
		return (ft_strdup("\0"));
	tail = tail_index(s1, set);
	new = (char *)malloc(sizeof(char) * (tail - head + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < tail - head + 1)
	{
		new[i] = s1[head + i];
		++i;
	}
	new[i] = '\0';
	return (new);
}
