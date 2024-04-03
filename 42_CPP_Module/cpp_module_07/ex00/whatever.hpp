/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 13:30:36 by kaye              #+#    #+#             */
/*   Updated: 2021/08/20 15:52:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

template< typename T >
void	swap(T & a, T & b) {
	T tmp = a;

	a = b;
	b = tmp;
}

template< typename T >
T const &	min(T const & a, T const & b) {
	if (a < b)
		return a;
	else
		return b;
}

template< typename T >
T const &	max(T const & a, T const & b) {
	if (a > b)
		return a;
	else
		return b;
}

#endif