/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:16:37 by flohrel           #+#    #+#             */
/*   Updated: 2021/12/12 19:43:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include "class.h"
# include "defs.h"

/*
 * parsing / run
 */
// BOOL		data_to_map(void);
BOOL		get_data(void);
void		run(void);

/*	
 * hash map
 */
uint32_t	get_hash(unsigned char *str);
BOOL		set_map(char *key, char *value);
t_map		*get_map(char *key);

/*
 * utils basic
 */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);

/*
 * utils clean
 */
void		free_clean(void **to_free);
void		clean(void);

/*
 * utils programme
 */
t_hr		*sgt(void);

#endif