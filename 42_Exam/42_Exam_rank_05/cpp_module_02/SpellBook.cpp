/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:21:28 by kaye              #+#    #+#             */
/*   Updated: 2021/09/09 20:49:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpellBook.hpp"

SpellBook::SpellBook(void) {}

SpellBook::~SpellBook(void) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();

	for (; it != ite; it++)
		delete *it;
	this->_spell.clear();
}

void SpellBook::learnSpell(ASpell *spell) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();
	
	for (; spell && it != ite; it++) {
		if ((*it)->getName() == spell->getName())
			return ;
	}
	this->_spell.push_back(spell->clone());
}

void SpellBook::forgetSpell(std::string const & spellName) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();

	for (; it != ite; it++) {
		if ((*it)->getName() == spellName) {
			delete *it;
			this->_spell.erase(it);
			return ;
		}
	}
}

ASpell*	SpellBook::createSpell(std::string const & spellName) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();

	for (; it != ite; it++) {
		if ((*it)->getName() == spellName)
			return *it;
	}
	return NULL;
}