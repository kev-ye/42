/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 18:24:37 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:46:36 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) :
	_name(name),
	_weapon(nullptr) {
	return ;
}

HumanB::~HumanB(void) {
	return ;
}

void	HumanB::attack(void) {
	if (this->_weapon == nullptr)
		return ;
	std::cout << this->_name << " attacks with his " \
		<< this->_weapon->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &weapon) {
	this->_weapon = &weapon;
}