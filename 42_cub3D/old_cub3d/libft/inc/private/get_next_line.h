/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:44:43 by kaye              #+#    #+#             */
/*   Updated: 2020/12/09 20:56:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct	s_set
{
	int				fd;
	char			*str;
	struct s_set	*next;
}				t_set;

t_set			*ft_lstnew_gnl(void);
void			ft_lstadd_front_gnl(t_set **alst, t_set *new);
void			ft_list_remove_gnl(t_set **alst);
char			*ft_strjoin_gnl(char const *s1, char const *s2);

#endif
