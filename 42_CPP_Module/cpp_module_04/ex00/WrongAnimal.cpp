/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:30:18 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:17:04 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : _type("Unknow") {
	std::cout << "\e[1;35mWrongAnimal\e[0m default constructor" << std::endl;
	return ;
}

WrongAnimal::WrongAnimal(std::string const & type) : _type(type) {
	std::cout << "\e[1;35mWrongAnimal\e[0m parameter constructor" << std::endl;
	return ;
}

WrongAnimal::WrongAnimal(WrongAnimal const & src) {
	std::cout << "\e[1;35mWrongAnimal\e[0m assignment constructor" << std::endl;
	*this = src;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "\e[1;35mWrongAnimal\e[0m destructor" << std::endl;
	return ;
}

std::string WrongAnimal::getType(void) const { return this->_type; }

void	WrongAnimal::makeSound() const {
	std::cout << "A WrongAnimal can't make sound!" << std::endl;
}

WrongAnimal & WrongAnimal::operator=(WrongAnimal const & rhs) {
	if (this == &rhs) return *this;

	this->_type = rhs._type;
	return *this;
}