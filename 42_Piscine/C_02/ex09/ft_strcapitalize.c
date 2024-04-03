/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:21:39 by kaye              #+#    #+#             */
/*   Updated: 2020/08/08 15:29:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_check_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int		ft_no_alphanum(char c)
{
	if (c >= 0 && c <= 47)
		return (1);
	else if (c >= 58 && c <= 64)
		return (1);
	else if (c >= 91 && c <= 96)
		return (1);
	else if (c >= 123 && c <= 127)
		return (1);
	return (0);
}

char	*ft_strcapitalize(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if ((i == 0 && ft_check_alpha(str[0])) ||
				(ft_check_alpha(str[i]) && ft_no_alphanum(str[i - 1])))
			str[i] -= 32;
		i++;
	}
	return (str);
}
