/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:24:34 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:18:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(void) : _type("Unknow") {}

AMateria::AMateria(std::string const & type) : _type(type) {}

AMateria::AMateria(AMateria const & src) { *this = src; }

AMateria::~AMateria(void) {}

std::string const &	AMateria::getType() const { return this->_type; }

void		AMateria::use(ICharacter & target) {
	std::cout << "AMateria base: " << target.getName() << std::endl;
}

AMateria &	AMateria::operator=(AMateria const & rhs) {
	if (this == &rhs) return *this;

	this->_type = rhs._type;
	return *this;
}