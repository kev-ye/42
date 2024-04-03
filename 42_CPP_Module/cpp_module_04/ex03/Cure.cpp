/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:50:40 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:19:18 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure") {}

Cure::Cure(Cure const & src) : AMateria(src) {}

Cure::~Cure(void) {}

AMateria	*Cure::clone(void) const { return new Cure(*this); }

void		Cure::use(ICharacter & target) {
	std::cout << "\e[1;32m* Heals " << target.getName()
		<< "'s wounds *\e[0m" << std::endl;
}

Cure &	Cure::operator=(Cure const & rhs) {
	if (this == &rhs) return *this;
	
	return *this;
}