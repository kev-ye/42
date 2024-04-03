/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:42:39 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 13:00:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"
#include <iomanip>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "usage: ./convert [\e[1;31mARGS\e[0m]" << std::endl;
		return (1);
	}

	Convert convert(av[1]);
	convert.display();
	return (0);
}