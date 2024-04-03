/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 22:30:57 by besellem          #+#    #+#             */
/*   Updated: 2021/05/16 02:21:05 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_strsfree(size_t size, char **s)
{
	if (s)
	{
		while (size-- > 0)
			ft_memdel((void **)(&s[size]));
		ft_memdel((void **)(&s));
	}
	return (NULL);
}
