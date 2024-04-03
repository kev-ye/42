/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:16:17 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:45:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
	Zombie kaye("kaye");
	Zombie *xue = newZombie("xue");

	xue->announce();
	randomChump("random");

	delete xue;
	return (0);
}