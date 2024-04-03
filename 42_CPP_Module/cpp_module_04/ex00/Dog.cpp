/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:47:23 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:16:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) {
	std::cout << "\e[1;36mDog\e[0m default constructor" << std::endl;
	this->_type = "Dog";
	return ;
}

Dog::Dog(Dog const & src) : Animal(src) {
	std::cout << "\e[1;36mDog\e[0m assignment constructor" << std::endl;
	return ;
}

Dog::~Dog(void) {
	std::cout << "\e[1;36mDog\e[0m destructor" << std::endl;
	return ;
}

void	Dog::makeSound(void) const {
	std::cout << "Wof wof ..." << std::endl;
}

Dog & Dog::operator=(Dog const & rhs) {
	if (this == &rhs) return *this;

	this->_type = rhs._type;
	return *this;
}