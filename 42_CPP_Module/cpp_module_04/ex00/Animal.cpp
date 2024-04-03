/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:30:18 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:16:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : _type("Unknow") {
	std::cout << "\e[1;35mAnimal\e[0m default constructor" << std::endl;
	return ;
}

Animal::Animal(std::string const & type) : _type(type) {
	std::cout << "\e[1;35mAnimal\e[0m parameter constructor" << std::endl;
	return ;
}

Animal::Animal(Animal const & src) {
	std::cout << "\e[1;35mAnimal\e[0m assignment constructor" << std::endl;
	*this = src;
}

Animal::~Animal(void) {
	std::cout << "\e[1;35mAnimal\e[0m destructor" << std::endl;
	return ;
}

std::string Animal::getType(void) const { return this->_type; }

void	Animal::makeSound() const {
	std::cout << "A Animal can't make sound!" << std::endl;
}

Animal & Animal::operator=(Animal const & rhs) {
	if (this == &rhs) return *this;
	
	this->_type = rhs._type;
	return *this;
}