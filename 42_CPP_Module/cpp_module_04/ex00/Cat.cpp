/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:47:23 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:16:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : Animal("Cat") {
	std::cout << "\e[1;34mCat\e[0m default constructor" << std::endl;
	return ;
}

Cat::Cat(Cat const & src) : Animal(src) {
	std::cout << "\e[1;34mCat\e[0m assignment constructor" << std::endl;
	return ;
}

Cat::~Cat(void) {
	std::cout << "\e[1;34mCat\e[0m destructor" << std::endl;
	return ;
}

void	Cat::makeSound(void) const {
	std::cout << "Miaouh miaouh ..." << std::endl;
}

Cat & Cat::operator=(Cat const & rhs) {
	if (this == &rhs) return *this;

	this->_type = rhs._type;
	return *this;
}