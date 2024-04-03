/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:15:02 by kaye              #+#    #+#             */
/*   Updated: 2021/08/20 16:16:52 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

int main(void) {
	std::cout << "\e[1;32m- Tab int -\e[0m" << std::endl;
	int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	iter<int>(tab, 10, print);

	std::cout << std::endl;

	std::cout << "\e[1;32m- Tab char -\e[0m" << std::endl;
	char c[] = {'a', 'b', 'c', 'd', 'A', 'B', 'C', 'D'};
	iter<char>(c, 8, print);

	std::cout << std::endl;

	std::cout << "\e[1;32m- Tab str -\e[0m" << std::endl;
	std::string str[] = {std::string("hello"), std::string("world")};
	iter<std::string>(str, 2, print);

	return 0;
} 