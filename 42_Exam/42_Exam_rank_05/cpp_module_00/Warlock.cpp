/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:27:54 by kaye              #+#    #+#             */
/*   Updated: 2021/09/09 15:52:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(std::string const & name, std::string const & title) :
	_name(name),
	_title(title) {
		std::cout << this->_name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock(void) {
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