/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 18:07:54 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:15:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) :
	_name("Unknow"),
	_hit_p(10),
	_energy_p(10),
	_attack_d(0) {
	std::cout << "\e[1;35mClapTrap\e[0m default constructor" << std::endl;
	return ;
}

ClapTrap::ClapTrap(std::string const & name) :
	_name(name),
	_hit_p(10),
	_energy_p(10),
	_attack_d(0) {
	std::cout << "\e[1;35mClapTrap\e[0m named parameter constructor" << std::endl;
	return ;
}

ClapTrap::ClapTrap(ClapTrap const & src) {
	std::cout << "\e[1;35mClapTrap\e[0m assignment constructor" << std::endl;
	*this = src;
	return ;
}

ClapTrap::~ClapTrap(void) {
	std::cout << "\e[1;35mClapTrap\e[0m destructor" << std::endl;
	return ;
}

void	ClapTrap::attack(std::string const & target) {
	if (this->_energy_p <= 0)
		std::cout << "ClapTrap [\e[1;32m" << this->_name \
		<< "\e[0m] isn't enough energy point. So he can't attack!" << std::endl;
	else {
		std::cout << "ClapTrap [\e[1;32m" << this->_name \
			<< "\e[0m] attacks [\e[1;31m" << target \
			<< "\e[0m], causing [\e[1;33m" << this->_attack_d \
			<< "\e[0m] points of damage!";
		this->_energy_p -= 10;
		std::cout << " (\e[0;33m" << this->_energy_p << "\e[0m energy points left)" << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount) {
	std::cout << "[\e[1;32m" << this->_name \
		<< "\e[0m] received a [\e[1;33m" << amount << "\e[0m] points of damage! ";

	if ((this->_hit_p -= amount) <= 0)
		std::cout << "[\e[1;32m" << this->_name << "\e[0m] Die!" << std::endl;
	else
		std::cout << "[\e[1;32m" << this->_name << "\e[0m] loss of [\e[1;33m" << amount \
		<< "\e[0m] hit points! (\e[0;33m" << this->_hit_p << "\e[0m hit points left)" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (this->_hit_p > 0) {
		std::cout << "[\e[1;32m" << this->_name \
			<< "\e[0m] Repairing ... He get [\e[1;33m"
			<< amount << "\e[0m] hit points! And [\e[1;33m" \
			<< amount << "\e[0m] energy points!" << std::endl;
		this->_hit_p += amount;
		this->_energy_p += amount;
	}
	else
		std::cout << "[\e[1;32m" << this->_name \
			<< "\e[0m] can't be repaired because it's died!" << std::endl;
}

int	ClapTrap::getAttackDamage(void) const { return this->_attack_d; }

std::string		ClapTrap::getName(void) const { return this->_name; }

ClapTrap & ClapTrap::operator=(ClapTrap const & rhs) {
	if (this == &rhs) return *this;
	
	this->_name = rhs._name;
	this->_hit_p = rhs._hit_p;
	this->_energy_p = rhs._energy_p;
	this->_attack_d = rhs._attack_d;
	return *this;
}