/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:47:23 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:17:13 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal("WrongCat") {
	std::cout << "\e[1;34mWrongCat\e[0m default constructor" << std::endl;
	return ;
}

WrongCat::WrongCat(WrongCat const & src) : WrongAnimal(src) {
	std::cout << "\e[1;34mWrongCat\e[0m assignment constructor" << std::endl;
	return ;
}

WrongCat::~WrongCat(void) {
	std::cout << "\e[1;34mWrongCat\e[0m destructor" << std::endl;
	return ;
}

void	WrongCat::makeSound(void) const {
	std::cout << this->getType() << ": Miaouh miaouh ..." << std::endl;
}

WrongCat & WrongCat::operator=(WrongCat const & rhs) {
	if (this == &rhs) return *this;

	this->_type = rhs._type;
	return *this;
}