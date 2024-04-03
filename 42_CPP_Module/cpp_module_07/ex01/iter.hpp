/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:15:24 by kaye              #+#    #+#             */
/*   Updated: 2021/08/20 16:11:03 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <cstddef>

template< typename T >
void	iter(T *array, size_t size, void (*f)(T const & value)) {
	for (size_t i = 0; i < size; i++)
		(*f)(array[i]);
}

template< typename T>
void	print(T const & value) {
	std::cout << value << std::endl;
}

#endif