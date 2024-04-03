/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 18:07:14 by kaye              #+#    #+#             */
/*   Updated: 2021/08/04 13:23:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main() {
	ClapTrap a("CL-69-1");
	ScavTrap b;
	ScavTrap c("SC-99-1");

	a.attack(b.getName());
	b.takeDamage(a.getAttackDamage());
	b.beRepaired(50);
	b.guardGate();
	c.attack(a.getName());
	a.takeDamage(c.getAttackDamage());

	return 0;
}