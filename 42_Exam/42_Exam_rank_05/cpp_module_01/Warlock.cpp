/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:27:54 by kaye              #+#    #+#             */
/*   Updated: 2021/09/09 20:21:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(std::string const & name, std::string const & title) :
	_name(name),
	_title(title) {
		std::cout << this->_name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock(void) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();

	for (; it != ite; it++)
		delete *it;
	this->_spell.clear();

	std::cout << this->_name << ": My job here is done!" << std::endl;
}

void	Warlock::introduce(void) const {
	std::cout << this->_name << ": I am " << this->_name << ", "
		<< this->_title << "!" << std::endl;
}

void	Warlock::setTitle(std::string const & title) {
	this->_title = title;
}

std::string const &	Warlock::getName(void) const { return this->_name; }
std::string const &	Warlock::getTitle(void) const { return this->_title; }

void Warlock::learnSpell(ASpell * spell) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();
	
	for (; spell && it != ite; it++) {
		if ((*it)->getName() == spell->getName())
			return ;
	}
	this->_spell.push_back(spell->clone());
}

void Warlock::forgetSpell(std::string const & spellName) {
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

void Warlock::launchSpell(std::string const & spellName, ATarget & target) {
	std::vector<ASpell*>::iterator it = this->_spell.begin();
	std::vector<ASpell*>::iterator ite = this->_spell.end();

	for (; it != ite; it++) {
		if ((*it)->getName() == spellName) {
			(*it)->launch(target);
			return ;
		}
	}
}