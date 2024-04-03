/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:29:00 by kaye              #+#    #+#             */
/*   Updated: 2022/01/09 21:02:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "libunit.h"
# include "function.h"

/**
 * @brief strlen tests
*/
int	strlen_launcher(void);
int	strlen_basic_test(void);
int	strlen_null_test(void);

/**
 * @brief strcpy tests
*/
int	strcpy_launcher(void);
int	strcpy_basic_test(void);
int	strcpy_bus_test(void);
int	strcpy_abrt_test(void);

/**
 * @brief strcmp tests
*/
int	strcmp_launcher(void);
int	strcmp_basic_test(void);
int	strcmp_null_test(void);

/**
 * @brief atoi tests
*/
int	atoi_launcher(void);
int	atoi_basic_test(void);
int	atoi_intmax_test(void);
int	atoi_intmin_test(void);
int	atoi_intmax_overflow_test(void);
int	atoi_intmin_overflow_test(void);
int	atoi_divise_by_zero_test(void);

/**
 * @brief strdup tests
*/
int	strdup_launcher(void);
int	strdup_basic_test(void);
int	strdup_abrt_test(void);

/**
 * @brief loop infini tests
*/
int	infini_launcher(void);
int	infini_loop_test(void);

#endif
