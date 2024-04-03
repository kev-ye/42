/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:44:43 by kaye              #+#    #+#             */
/*   Updated: 2021/03/09 21:14:51 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 4096

typedef struct s_set
{
	int				fd;
	char			*str;
	struct s_set	*next;
}				t_set;

typedef struct s_v3
{
	t_set			*tmp;
	char			buff[BUFFER_SIZE + 1];
	int				ret;
	t_set			*tmp_set;
}				t_v3;

t_set			*ft_lstnew_gnl(void);
void			ft_lstadd_front_gnl(t_set **alst, t_set *new);
void			ft_list_remove_gnl(t_set **alst);
size_t			ft_strlen_gnl(const char *s);
char			*ft_strjoin_gnl(char const *s1, char const *s2);

#endif
