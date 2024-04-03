/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 22:07:09 by besellem          #+#    #+#             */
/*   Updated: 2021/05/10 22:44:15 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	**ft_split(char const *s, char c)
{
	const char	charset[2] = {c, '\0'};

	return (ft_strsplit(s, charset));
}
