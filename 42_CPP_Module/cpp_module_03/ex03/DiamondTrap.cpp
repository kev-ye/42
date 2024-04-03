/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 13:30:05 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:15:47 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void) : 
	ClapTrap(),
	ScavTrap(),
	FragTrap(),
	_name("Unknow") {
	std::cout << "\e[1;34mDiamondTrap\e[0m default constructor" << std::endl;
	this->ClapTrap::_name = "Unknow_clap_name";
	this->FragTrap::setHP();
	this->ScavTrap::setEP();
	this->FragTrap::setAD();
};

DiamondTrap::DiamondTrap(std::string const & name) :
	ClapTrap(name),
	ScavTrap(name),
	FragTrap(name),
	_name(name) {
	std::cout << "\e[1;34mDiamondTrap\e[0m named parameter constructor" << std::endl;
	this->ClapTrap::_name = name + "_clap_name";
	this->FragTrap::setHP();
	this->ScavTrap::setEP();
	this->FragTrap::setAD();
};

DiamondTrap::DiamondTrap(DiamondTrap const & src) {
	std::cout << "\e[1;34mDiamondTrap\e[0m assignment constructor" << std::endl;
	*this = src;
}

DiamondTrap::~DiamondTrap(void) {
	std::cout << "\e[1;34mDiamondTrap\e[0m destructor" << std::endl;
}

DiamondTrap & DiamondTrap::operator=(DiamondTrap const & rhs) {
	if (this == &rhs) return *this;
	
	this->_name = rhs._name;
	this->_hit_p = rhs._hit_p;
	this->_energy_p = rhs._energy_p;
	this->_attack_d = rhs._attack_d;
	return *this;
}

void	DiamondTrap::attack(std::string const & target) {
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI(void) {
	std::cout << "I am [\e[1;32m" << this->_name << "]\e[0m and my ClapTrap name is [\e[1;32m" \
		<< this->ClapTrap::_name << "]\e[0m." << std::endl;
}