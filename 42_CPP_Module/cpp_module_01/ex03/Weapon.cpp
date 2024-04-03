/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 18:24:45 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:46:50 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string weapon_type) : _weapon_type(weapon_type) {
	return ;
}

Weapon::~Weapon() {
	return ;
}

std::string const	&Weapon::getType(void) const {
	return (this->_weapon_type);
}

void				Weapon::setType(std::string to_set) {
	this->_weapon_type = to_set;
}