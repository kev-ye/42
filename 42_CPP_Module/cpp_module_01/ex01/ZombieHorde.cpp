/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:46:08 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:46:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
	Zombie *zombie_horde = new Zombie[N];
	
	for (int i = 0; i < N; i++) {
		
		zombie_horde[i].set_name(name);
	}
	return (zombie_horde);
}