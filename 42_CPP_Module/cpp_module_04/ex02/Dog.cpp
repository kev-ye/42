/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:47:23 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:18:43 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal("Oog") {
	std::cout << "\e[1;36mDog\e[0m default constructor" << std::endl;
	this->_brain = new Brain();
	return ;
}

Dog::Dog(Dog const & src) : Animal(src) {
	std::cout << "\e[1;36mDog\e[0m assignment constructor" << std::endl;
	this->_brain = new Brain(*(src._brain));
	return ;
}

Dog::~Dog(void) {
	std::cout << "\e[1;36mDog\e[0m destructor" << std::endl;
	delete this->_brain;
	return ;
}

void	Dog::makeSound(void) const {
	std::cout << "Wof wof ..." << std::endl;
}

Brain	*Dog::getBrain(void) const {
	return this->_brain;
}

Dog & Dog::operator=(Dog const & rhs) {
	if (this == &rhs) return *this;
	
	if (this->_brain)
		delete this->_brain;
	this->_type = rhs._type;
	this->_brain = new Brain(*(rhs._brain));
	return *this;
}