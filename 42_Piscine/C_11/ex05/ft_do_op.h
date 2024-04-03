/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 17:13:04 by kaye              #+#    #+#             */
/*   Updated: 2020/08/24 10:53:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DO_OP_H
# define FT_DO_OP_H
# include <unistd.h>

int		ft_atoi(char *str);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
int		ft_addition(int a, int b);
int		ft_soustraction(int a, int b);
int		ft_multiplication(int a, int b);
int		ft_division(int a, int b);
int		ft_modulo(int a, int b);

#endif
