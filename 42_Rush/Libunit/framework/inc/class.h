/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:11:05 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 16:22:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS_H
# define CLASS_H

typedef struct s_test
{
	char const		*func_name;
	char const		*test_name;
	int				(*func)(void);
	struct s_test	*next;
}	t_test;

typedef struct s_result
{
	int	result_success;
	int	result_failure;
}	t_result;

typedef struct s_unit
{
	t_result	info;
	t_test		*test;
}	t_unit;

#endif