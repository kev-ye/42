/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 11:41:47 by kaye              #+#    #+#             */
/*   Updated: 2020/08/23 20:23:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_02_H
# define RUSH_02_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int					ft_strlen(char *str);
void				ft_putstr(char *str);
int					ft_atoi(char *str);
int					is_space(char c);
int					is_number(char c);
int					to_find(char *str, char *to_find);
int					ft_strcmp(char *s1, char *s2);
int					ft_strcmp_nbr(char *s1, char *s2);
int					sep(char c, char *charset);
int					words(char *str, char *charset);
int					l_w(char *str, char *charset, int i);
char				**split(char *str, char *sepa, char **tab);
char				**ft_split(char *str, char *charset);
int					ft_strlen_plus(int size, char **strs);
char				*ft_malloc_word_strjoin(int size, char **strs, char *sep);
char				*ft_strjoin(int size, char **strs, char *sep);
int					check_dic(char *dic);
int					check_argv_number(char *av);
int					ft_open_valid(char *path);
int					ft_open_count(char *path);
char				*ft_open_malloc(char *path);
void				ft_error(int error);
int					ft_strlentab(char **tab);
int					wordsentry(char *str, char *charset);
int					l_entry(char *str, char *charset, int i);
char				**split_entry(char *str, char *sepa, char **tab);
char				**ft_split2(char *str, char *charset);
void				print_dic(char *av);
char				*malloc_tab(char *str, char *sep, int i);

typedef struct		s_variable
{
	int i;
	int x;
	int y;
}					t_variable;

#endif
