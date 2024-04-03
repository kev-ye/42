/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 18:07:14 by kaye              #+#    #+#             */
/*   Updated: 2021/08/04 13:29:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main() {

	FragTrap a;
	FragTrap b("FR-78-1");
	ScavTrap c("SC-98-1");
	ScavTrap d("SC-99-1");

	a.attack(c.getName());
	c.takeDamage(a.getAttackDamage());
	c.attack(a.getName());
	c.beRepaired(50);
	c.guardGate();
	a.attack(d.getName());
	d.takeDamage(a.getAttackDamage());
	b.attack(d.getName());
	d.takeDamage(b.getAttackDamage());
	d.attack(b.getName());
	b.takeDamage(d.getAttackDamage());
	a.attack(d.getName());
	d.takeDamage(a.getAttackDamage());
	b.attack(d.getName());
	d.takeDamage(b.getAttackDamage());
	d.guardGate();
	a.highFivesGuys();
	return 0;
}