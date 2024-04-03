/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:47:23 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:18:33 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) : Animal("Cat") {
	std::cout << "\e[1;34mCat\e[0m default constructor" << std::endl;
	this->_brain = new Brain();
	return ;
}

Cat::Cat(Cat const & src) : Animal(src) {
	std::cout << "\e[1;34mCat\e[0m assignment constructor" << std::endl;
	this->_brain = new Brain(*(src._brain));
	return ;
}

Cat::~Cat(void) {
	std::cout << "\e[1;34mCat\e[0m destructor" << std::endl;
	delete this->_brain;
	return ;
}

void	Cat::makeSound(void) const {
	std::cout << "Miaouh miaouh ..." << std::endl;
}

Brain	*Cat::getBrain(void) const {
	return this->_brain;
}

Cat & Cat::operator=(Cat const & rhs) {
	if (this == &rhs) return *this;
	
	if (this->_brain)
		delete this->_brain;
	this->_type = rhs._type;
	this->_brain = new Brain(*(rhs._brain));
	return *this;
}