/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:03:51 by besellem          #+#    #+#             */
/*   Updated: 2021/04/18 10:32:22 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allow to write an int without creating a variable beforehand
** (like ft_putchar for integers or equivalent to putchar in the C standard)
** ex:
**
** int nb = 12;
** write(1, &nb, 4);
**
** <=> is now equivalent to:
**
** ft_putn(12, 4);
** or
** ft_putn_fd(1, 12, 4);
**
** From the same family:
** void		ft_putn_fd(int fd, int c, int bytes);
** void		ft_putn(int c, int bytes);
** void		ft_putc_fd(int c, int fd);
** void		ft_putc(int c);
**
** All of these have the same utility but are slightly different depending on
** the use case.
** ft_putn_fd will write `c` into a `fd` with a length of `bytes`.
** ft_putn is equivalent to ft_putn_fd(1, c, bytes)
** ft_putc_fd will write `c` into a `fd` with a length of 1.
** ft_putc is equivalent to ft_putc_fd(c, 1)
*/

void	ft_putc(int c)
{
	ft_putc_fd(c, STDOUT_FILENO);
}
