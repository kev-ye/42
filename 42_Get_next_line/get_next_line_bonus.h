/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:44:43 by kaye              #+#    #+#             */
/*   Updated: 2020/11/21 20:55:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_set
{
	int				fd;
	char			*str;
	struct s_set	*next;
}				t_set;

t_set			*ft_lstnew_gnl(void);
void			ft_lstadd_front_gnl(t_set **alst, t_set *new);
void			ft_list_remove_gnl(t_set **alst);
size_t			ft_strlen(const char *s);
char			*ft_strjoin_gnl(char const *s1, char const *s2);
int				get_next_line(int fd, char **line);

#endif
