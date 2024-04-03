/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongDog.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:47:23 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:17:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongDog.hpp"

WrongDog::WrongDog(void) : WrongAnimal("WrongDog") {
	std::cout << "\e[1;36mWrongDog\e[0m default constructor" << std::endl;
	return ;
}

WrongDog::WrongDog(WrongDog const & src) : WrongAnimal(src) {
	std::cout << "\e[1;36mWrongDog\e[0m assignment constructor" << std::endl;
	return ;
}

WrongDog::~WrongDog(void) {
	std::cout << "\e[1;36mWrongDog\e[0m destructor" << std::endl;
	return ;
}

void	WrongDog::makeSound(void) const {
	std::cout << this->getType() << ": Wof wof ..." << std::endl;
}

WrongDog & WrongDog::operator=(WrongDog const & rhs) {
	if (this == &rhs) return *this;
	
	this->_type = rhs._type;
	return *this;
}