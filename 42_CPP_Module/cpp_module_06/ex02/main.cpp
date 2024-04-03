/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:39:02 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 17:02:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main() {
	Base *base;
	
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		std::cout << "Test [\e[1;32m" << i + 1 << "\e[0m]: " << std::endl;
	
		base = generate();
		std::cout << "*\e[1;34m";
		identify_from_pointer(base);
		std::cout << "\e[0m, &\e[1;36m";
		identify_from_reference(*base);

		std::cout << "\e[0m\n" << std::endl;
		delete base;
	}
	return (0);
}