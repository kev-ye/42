/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 18:07:14 by kaye              #+#    #+#             */
/*   Updated: 2021/08/07 14:35:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main() {
	DiamondTrap a("DI");

	a.whoAmI();
	a.attack("Unknow");
	a.takeDamage(10);
	a.beRepaired(10);
	a.guardGate();
	a.highFivesGuys();
	
	return 0;
}