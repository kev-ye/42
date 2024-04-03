/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:45:43 by besellem          #+#    #+#             */
/*   Updated: 2021/06/22 13:53:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Bitshift value for double quotes */
#define DBL_BSHFT 0

/* Bitshift value for simple quotes */
#define SGL_BSHFT 1

/*
** - find out if a quote has been found already
** - find out which type of quotes has already been found
** - find out which quote was the first and has to be closed
** - find out if a quote has to be closed
*/
int	quotes2close(unsigned char c, t_quotes *q, int status)
{
	if (QUOTES_RESET_FLAG == status)
	{
		ft_bzero(q, sizeof(t_quotes));
		return (0);
	}
	q->did_change = ((1 == q->d_quote) || (1 == q->s_quote));
	if (QUOTES_SET_FLAG == status)
	{
		if ((('"' == c) && (('"' == c) << DBL_BSHFT) & q->first)
			|| (('\'' == c) && (('\'' == c) << SGL_BSHFT) & q->first))
			q->first = 0;
		else if (0 == q->d_quote && 0 == q->s_quote)
			q->first = (('"' == c) << DBL_BSHFT) | (('\'' == c) << SGL_BSHFT);
		if (('\'' == c) && 0 == q->d_quote)
			q->s_quote = (0 == q->s_quote);
		else if (('"' == c) && 0 == q->s_quote)
			q->d_quote = (0 == q->d_quote);
	}
	q->did_change = (q->did_change != ((1 == q->d_quote) || (1 == q->s_quote)));
	return (q->first != 0);
}
