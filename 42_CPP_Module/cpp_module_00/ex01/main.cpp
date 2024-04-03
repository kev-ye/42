/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:57:07 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:43:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

int main(void) {

	PhoneBook		book;
	std::string	cmd;
	bool		color_set = true;

	do {
		book.menu();

		if (color_set == true)
			std::cout << ANSI_GREEN"# " ANSI_NONE;
		else
			std::cout << ANSI_RED"# " ANSI_NONE;

		std::getline(std::cin, cmd);
		if (std::cin.eof() || cmd == "EXIT")
			book.exit();
		else if (cmd == "ADD") {	
			color_set = true;
			book.add_contact();
		}
		else if (cmd == "SEARCH") {
			color_set = true;
			book.search_contact();
		}
		else {
			color_set = false;
			std::cout << ANSI_RED"Cmd not found !\n" ANSI_NONE << std::endl;
		}
	} while (true);
	return (0);
}