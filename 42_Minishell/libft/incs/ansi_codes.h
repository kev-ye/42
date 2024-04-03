/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_codes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:08:23 by besellem          #+#    #+#             */
/*   Updated: 2021/05/10 00:26:33 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSI_CODES_H
# define ANSI_CODES_H

/*
** -- COLORS --
** Normal
*/
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GRAY "\033[0;37m"

/*
** Bold
*/
# define B_BLACK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\033[1;34m"
# define B_PURPLE "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define B_GRAY "\033[1;37m"

/*
** Foreground
*/
# define F_BLACK "\033[40m"
# define F_RED "\033[41m"
# define F_GREEN "\033[42m"
# define F_YELLOW "\033[43m"
# define F_BLUE "\033[44m"
# define F_PURPLE "\033[45m"
# define F_CYAN "\033[46m"
# define F_GRAY "\033[47m"

/*
** -- CLEAR CODES --
*/
# define CLR_COLOR "\033[0m"
# define CLR_LINE "\033[2K\r"
# define CLR_SCREEN "\033[2J\033[H"

/*
** -- OTHERS --
*/
# define BELL "\a"					// play terminal's bell sound
# define INVISIBLE_CURSOR "\e[?25l"	// make the cursor invisible
# define VISIBLE_CURSOR "\e[?25h"	// make the cursor visible (again)

#endif
