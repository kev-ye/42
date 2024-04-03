/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lrv_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:12:23 by kaye              #+#    #+#             */
/*   Updated: 2021/06/22 14:20:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_wifsignaled(int status)
{
	return (_wstatus(status) != 0177 && _wstatus(status) != 0);
}

int	_wtermsig(int status)
{
	return (_wstatus(status));
}
