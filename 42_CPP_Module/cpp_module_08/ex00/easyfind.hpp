/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:21:48 by kaye              #+#    #+#             */
/*   Updated: 2021/08/22 19:02:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <exception>

template< typename T >
int	easyfind(T container, int const toFind) {
	typename T::iterator it = std::find(container.begin(), container.end(), toFind);
	if (it != container.end())
		return *it;
	throw std::exception();
}

/* main test template function */
template< typename T >
void	tryToFind(T container, int nbr) {
	try {
		std::cout << "\e[1;35mTo find:\e[0m " << nbr << std::endl;
		std::cout << "\e[1;36mFind:\e[0m " << easyfind< T >(container, nbr) << std::endl;
	}
	catch (std::exception & e) {
		std::cout << "\e[1;31mCan't found number!\e[0m" << std::endl;
	}
}

#endif