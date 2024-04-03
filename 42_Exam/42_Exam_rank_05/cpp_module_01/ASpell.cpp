/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:38:54 by kaye              #+#    #+#             */
/*   Updated: 2021/09/10 18:03:52 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

ASpell::ASpell(void) :
	_name(),
	_effects() {}

ASpell::ASpell(std::string const & name, std::string const & effects) :
	_name(name),
	_effects(effects) {}

ASpell::ASpell(ASpell const & src) { *this = src; }

ASpell::~ASpell(void) {}

ASpell & ASpell::operator=(ASpell const & rhs) {
	if (this == &rhs) return *this;

	this->_name = rhs._name;
	this->_effects = rhs._effects;
	return *this;
}

std::string const & ASpell::getName(void) const { return this->_name; }
std::string const & ASpell::getEffects(void) const { return this->_effects; }

void ASpell::launch(ATarget const & target) {
	target.getHitBySpell(*this);
}