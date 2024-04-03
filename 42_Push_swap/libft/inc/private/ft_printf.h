/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 22:34:03 by kaye              #+#    #+#             */
/*   Updated: 2021/03/28 19:52:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** NORMAL
*/
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"

/*
** BACKGROUND
*/
# define F_BLACK "\033[40m"
# define F_RED "\033[41m"
# define F_GREEN "\033[42m"
# define F_YELLOW "\033[43m"
# define F_BLUE "\033[44m"
# define F_PURPLE "\033[45m"
# define F_CYAN "\033[46m"

/*
** CLEAR
*/
# define NONE "\033[0m"
# define CLR "\033[2J\033[H"

/*
** Printf family
*/
int		ft_vprintf(const char *format, va_list arg);

#endif
