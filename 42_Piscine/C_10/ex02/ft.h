/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:12:00 by kaye              #+#    #+#             */
/*   Updated: 2020/08/24 18:05:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <libgen.h>
# include <sys/errno.h>
# define BUF_MAX 4092

char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	ft_putstr_fd(int fd, char *str);
void	ft_error(char *orgin, char *path, char *err);
void	print_name_path(char *path);
char	*stock_file(int fd, int *size);
int		ft_tail(char *path, int condition, int count, int print_path);

#endif
