/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:29:50 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 13:15:06 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# define B_BLACK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\033[1;34m"
# define B_PURPLE "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define NONE "\033[0m"
# define S_CLRLINE "\033[K\r"
# define ERROR 1
# define SUCCESS 0
# define BUFFER_SIZE_PN 11

size_t	ft_strlen(const char *s);
void	ft_putchar(char c);
void	ft_putstr(char *s);
int		ft_atoi(const char *str);
void	ft_putnbr(int n);
char	*add_c2str(char const *s1, char c);
void	load_bar(long long current, long long max);
#endif
