/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 18:54:22 by besellem          #+#    #+#             */
/*   Updated: 2021/05/07 12:58:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strcat(char *s1, const char *s2)
{
	const size_t	len = ft_strlen(s1);
	size_t			i;

	i = 0;
	while (s2[i])
	{
		s1[len + i] = s2[i];
		++i;
	}
	s1[len + i] = '\0';
	return (s1);
}
