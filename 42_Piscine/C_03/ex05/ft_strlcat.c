/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:10:46 by kaye              #+#    #+#             */
/*   Updated: 2020/08/13 15:21:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_strlen(char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_src;

	i = 0;
	j = 0;
	len_src = ft_strlen(src);
	while (dest[i] != '\0' && i < size)
		i++;
	if (size > 0)
	{
		while (src[j] != '\0' && i < size - 1)
			dest[i++] = src[j++];
	}
	if (j != 0)
	{
		dest[i] = '\0';
		return (len_src + (i - j));
	}
	return (len_src + i);
}
