/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rush.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:40:15 by kaye              #+#    #+#             */
/*   Updated: 2020/08/16 19:40:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RUSH_H
# define FT_RUSH_H
# include <stdlib.h>
# include <unistd.h>

void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_print_tab(int **tab);
void			ft_init_tab(int **tab);
int				ft_check_raw(int number, int row, int **tab);
int				ft_check_col(int number, int col, int **tab);
int				ft_check_raw_left_with_condition(int raw, int **tab,
		int *condition);
int				ft_check_raw_right_with_condition(int raw, int **tab,
		int *condition);
int				ft_check_col_up_with_condition(int col, int **tab,
		int *condition);
int				ft_check_col_down_with_condition(int col, int **tab,
		int *condition);
int				ft_is_valide(int **tab, int position, int *condition);
int				check_param(char *str);
int				ft_strlen2(char **argv);
typedef struct	s_variables
{
	int raw;
	int col;
	int number;
}				t_variables;

#endif
