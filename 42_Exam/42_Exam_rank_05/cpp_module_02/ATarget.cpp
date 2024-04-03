/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:18:51 by kaye              #+#    #+#             */
/*   Updated: 2021/09/09 20:22:52 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

ATarget::ATarget(void) : _type() {}

ATarget::ATarget(std::string const & type) : _type(type) {}

ATarget::ATarget(ATarget const & src) { *this = src; }

ATarget::~ATarget(void) {}

ATarget & ATarget::operator=(ATarget const & rhs) {
	if (this == &rhs) return *this;

	this->_type = rhs._type;
	return *this;
}

std::string const & ATarget::getType(void) const { return this->_type; }

void	ATarget::getHitBySpell(ASpell const & spell) const {
	std::cout << this->_type << " has been " << spell.getEffects()
		<< "!" << std::endl;
}