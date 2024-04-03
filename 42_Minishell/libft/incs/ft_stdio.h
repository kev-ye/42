/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:25:41 by besellem          #+#    #+#             */
/*   Updated: 2021/04/19 13:11:45 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include <unistd.h>

# include "ft_printf.h"

void	ft_putn(int c, int bytes);
void	ft_putn_fd(int fd, int c, int bytes);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putaddr(void *addr);
void	ft_putaddr_fd(void *addr, int fd);

void	ft_putc(int c);
void	ft_putc_fd(int c, int fd);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnstr(char *s, size_t n);
void	ft_putnstr_fd(char *s, int fd, size_t n);
void	ft_putendl(char *s);
void	ft_putendl_fd(char *s, int fd);

int		get_next_line(int fd, char **line);

#endif
