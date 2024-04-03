/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lrv_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:34:34 by kaye              #+#    #+#             */
/*   Updated: 2021/06/22 14:12:47 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_wstatus(int status)
{
	return (status & 0177);
}

int	_wifexited(int status)
{
	return (_wstatus(status) == 0);
}

#if __DARWIN_UNIX03
int	_wexitstatus(int status)
{
	return ((status >> 8) & 0x000000ff);
}
#else

int	_wexitstatus(int status)
{
	return (status >> 8);
}
#endif
