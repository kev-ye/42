/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:46:10 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:46:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	int     to_new(5);
	Zombie  *kaye = zombieHorde(to_new, "kaye");

	for (int i = 0; i < to_new; i++) {
		
		std::cout << "Zombie index : [" << i << "] : ";
		kaye[i].announce();
	}
 
	delete [] kaye;
	return (0);
}