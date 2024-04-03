/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 19:39:42 by kaye              #+#    #+#             */
/*   Updated: 2020/08/18 17:46:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*save;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (src[len])
		len++;
	if (!(save = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (src[++i])
		save[i] = src[i];
	save[i] = '\0';
	return (save);
}
