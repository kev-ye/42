/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 09:41:23 by wiozsert          #+#    #+#             */
/*   Updated: 2020/08/27 12:03:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_solver
{
	int		empty;
	int		obstacle;
	int		fill;
	int		*string_tray;
}				t_solver;

typedef struct	s_tab
{
	char		*str;
}				t_tab;

typedef struct	s_squart
{
	int		len;
	int		i;
	int		j;
}				t_squart;

int				ft_strlen(char *str);
char			*ft_strdup(char *src);
void			ft_putstr_error(char *str);
void			ft_putchar_error(char c);
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				*ft_init_str_from_file(char *tray, int *str);
int				**ft_init_tab_from_str(int *str, int **tab);
int				ft_check_if_tray_is_full_of_obstacle(int *str);
int				ft_check_if_char_is_missing(int *str, int obstacle, int empty);
int				ft_check_if_char_is_found(int *str, int empty, int obstacle);
int				ft_check_if_line_are_same_length(int *str, int i,
												int j, int length);
int				ft_check_if_tray_is_empy(int *str);
int				ft_check_valid_tray(int *str, t_solver solver);
void			ft_get_empty(int *str, int *empty);
void			ft_get_obstacle(int *str, int *obstacle);
void			ft_get_fill(int *str, int *fill);
int				**ft_init_stock(int **stock, int **tab,
								int empty, int obstacle);
t_squart		check_sq(int **map);
void			ft_solve_tab(int **tab, int empty, int obstacle);
int				**replace_tab(int **map, t_squart sq, char fill);
void			show_tab(int **map);
int				ft_resolve_tray(char *tray, int **tab);
int				*ft_copy_stin_in_tab(int *buffer);
char			*ft_malloc_tab_in_string(char *string, char *buffer);
char			*ft_copy_tab_in_string(char *string, char *buffer);
int				ft_resolve_tray_one_ac(int *buffer);
void			ft_free_for_all(int **tab, int **stock, t_solver solver);

#endif
