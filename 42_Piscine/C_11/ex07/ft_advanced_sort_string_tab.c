/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_string_tab.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 10:18:01 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/24 10:23:13 by wiozsert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *, char *))
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (tab[i] != 0)
	{
		if (tab[i + 1] != 0)
			j = i + 1;
		if (cmp(tab[i], tab[j]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[j];
			tab[j] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
