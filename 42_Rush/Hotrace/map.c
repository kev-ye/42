/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:28:26 by flohrel           #+#    #+#             */
/*   Updated: 2021/12/12 17:44:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

uint32_t	get_hash(unsigned char *str)
{
	uint32_t	hash_val;
	uint32_t	power_of_p;

	hash_val = 0;
	power_of_p = 1;
	while (*str)
	{
		hash_val = (hash_val + (*str + 1) * power_of_p) % HASH_MAX;
		power_of_p = (power_of_p * HASH_PRIME) % HASH_MAX;
		str++;
	}
	return (((hash_val % HASH_MAX) + HASH_MAX) % HASH_MAX);
}

t_map	*get_map(char *key)
{
	t_hr		*ptr;
	t_map		*entry;
	uint32_t	hash;

	ptr = sgt();
	hash = get_hash((unsigned char *)key);
	entry = ptr->hash_map[hash];
	while (entry)
	{
		if (0 == ft_strcmp(entry->key, key))
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}

static BOOL	_check_if_collision(t_map *new, uint32_t hash)
{
	t_hr	*ptr;
	t_map	*tmp;
	t_map	*add_to_next;

	ptr = sgt();
	if (NULL != ptr->hash_map[hash])
	{
		tmp = ptr->hash_map[hash];
		while (tmp)
		{
			add_to_next = tmp;
			if (0 == ft_strcmp(tmp->key, new->key))
				return (FALSE);
			tmp = tmp->next;
		}
		add_to_next->next = new;
	}
	else
		ptr->hash_map[hash] = new;
	return (TRUE);
}

BOOL	set_map(char *key, char *value)
{
	t_map		*new;
	uint32_t	hash;

	new = ft_calloc(1, sizeof(t_map));
	if (NULL == new)
		return (FALSE);
	new->key = key;
	new->value = value;
	new->next = NULL;
	hash = get_hash((unsigned char *)key);
	if (FALSE == _check_if_collision(new, hash))
		free_clean((void **)&new);
	return (TRUE);
}
