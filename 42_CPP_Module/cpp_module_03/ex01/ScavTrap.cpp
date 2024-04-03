/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 13:02:52 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:14:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap("Unknow") {
	std::cout << "\e[1;36mScavTrap\e[0m default constructor" << std::endl;
	this->_hit_p = 100;
	this->_energy_p = 50;
	this->_attack_d = 20;
	return ;
}

ScavTrap::ScavTrap(std::string const & name) : ClapTrap(name) {
	std::cout << "\e[1;36mScavTrap\e[0m named parameter constructor" << std::endl;
	this->_hit_p = 100;
	this->_energy_p = 50;
	this->_attack_d = 20;
	return ;
}

ScavTrap::ScavTrap(ScavTrap const & src) {
	std::cout << "\e[1;36mScavTrap\e[0m assignment constructor" << std::endl;
	*this = src;
	return ;
}

ScavTrap::~ScavTrap(void) {
	std::cout << "\e[1;36mScavTrap\e[0m destructor" << std::endl;
	return ;
}

void	ScavTrap::attack(std::string const & target) {
	if (this->_energy_p <= 0)
		std::cout << "ScavTrap [\e[1;32m" << this->_name \
		<< "\e[0m] isn't enough energy point. So he can't attack!" << std::endl;
	else {
		std::cout << "ScavTrap [\e[1;32m" << this->_name \
			<< "\e[0m] attacks [\e[1;31m" << target \
			<< "\e[0m], causing [\e[1;33m" << this->_attack_d \
			<< "\e[0m] points of damage!";
		this->_energy_p -= 10;
		std::cout << " (\e[33m" << this->_energy_p << "\e[0m energy points left)" << std::endl;
	}
}

void	ScavTrap::guardGate(void) {
	if (this->_hit_p > 0)
		std::cout << "ScavTrap [\e[1;32m" << this->_name \
			<< "\e[0m] is now guard gate!" << std::endl;
	else
		std::cout << "ScavTrap [\e[1;32m" << this->_name \
			<< "\e[0m] can't be guard gate because it's died!" << std::endl;
}

ScavTrap	& ScavTrap::operator=(ScavTrap const & rhs) {
	if (this == &rhs) return *this;

	this->_name = rhs._name;
	this->_hit_p = rhs._hit_p;
	this->_energy_p = rhs._energy_p;
	this->_attack_d = rhs._attack_d;
	return *this;
}
