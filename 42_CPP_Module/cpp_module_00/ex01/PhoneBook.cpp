/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:40:50 by kaye              #+#    #+#             */
/*   Updated: 2021/10/17 13:40:57 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook (void) : _book_i(0) {
	return ;
}

PhoneBook::~PhoneBook (void) {
	for (int i = 0; i < BOOK_NBR; i++)
		this->_book[i].info_clean();
	return ;
}

void	PhoneBook::exit(void) const {
	std::cout << ANSI_RED "Exit !" ANSI_NONE << std::endl;
	std::exit(EXIT_SUCCESS);
}

void	PhoneBook::_input_value(std::string &tmp) const {
	tmp.clear();

	std::getline (std::cin, tmp);
	if (std::cin.eof() == true)
		this->exit();
}

void	PhoneBook::_show_search_contact_line(int info, int index) const {
	std::cout << '|';
	if (this->_book[index].get_info(info).length() > 9)
		std::cout << this->_book[index].get_info(info).substr(0, 9) << '.';
	else
		std::cout << std::setw(10) << this->_book[index].get_info(info);
}

void	PhoneBook::_print_search_contact(int index) const {
	const char *info_name[] = {
		"First name : ",
		"Last name : ",
		"Nickname : ",
		"Phone number : ",
		"darkest secret : "};

	for (int i = 0; i < INFO_NBR; i++) {
		std::cout << info_name[i];
		std::cout << this->_book[index].get_info(i) << std::endl;
	}
	std::cout << std::endl;
}

void	PhoneBook::add_contact(void) {
	std::string tmp;

	this->_book[this->_book_i].info_clean();

	std::cout << std::setw(4) << "" << "-> Enter the first name : ";
	this->_input_value(tmp);
	this->_book[this->_book_i].set_info(tmp, e_FIRST_NAME);

	std::cout << std::setw(4) << "" << "-> Enter the last name : ";
	this->_input_value(tmp);
	this->_book[this->_book_i].set_info(tmp, e_LAST_NAME);

	std::cout << std::setw(4) << "" << "-> Enter the nickname : ";
	this->_input_value(tmp);
	this->_book[this->_book_i].set_info(tmp, e_NICKNAME);

	std::cout << std::setw(4) << "" << "-> Enter the phone number : ";
	this->_input_value(tmp);
	this->_book[this->_book_i].set_info(tmp, e_PHONE_NBR);

	std::cout << std::setw(4) << "" << "-> Enter the darkest secret : ";
	this->_input_value(tmp);
	this->_book[this->_book_i].set_info(tmp, e_DARKEST_SECRET);

	std::cout << std::endl;

	if (this->_book[this->_book_i].info_is_empty() == false)
		++this->_book_i;
	if (this->_book_i >= BOOK_NBR) {
		this->_book_i = 0;
		std::cout << ANSI_RED"Book is full !\n" ANSI_NONE;
		std::cout << ANSI_RED"Next cmd ADD will overwrite (index -> 0) !\n" ANSI_NONE << std::endl;
	}
}

void	PhoneBook::search_contact(void) const {
	std::string	tmp;
	long		index = -1;
	char 		*ptr = NULL;

	for (int i = 0; i < BOOK_NBR; i++) {
		if (this->_book[i].info_is_empty() == true) {
			if (i == BOOK_NBR - 1) {
				std::cout << ANSI_RED "Book is empty !\n" ANSI_NONE << std::endl;
				return ;
			}
			continue ;
		}
		else
			break ;
	}

	std::cout << "|----------|----------|----------|----------|" << std::endl;
	std::cout << "|     index|first name| last name|  nickname|" << std::endl;
	std::cout << "|----------|----------|----------|----------|" << std::endl;

	for (int i = 0; i < BOOK_NBR; i++) {
		if (this->_book[i].info_is_empty() == true)
			continue ;
		std::cout << '|';
		std::cout << std::setw(10) << i + 1;
		this->_show_search_contact_line(e_FIRST_NAME, i);
		this->_show_search_contact_line(e_LAST_NAME, i);
		this->_show_search_contact_line(e_NICKNAME, i);
		std::cout << '|' << std::endl;
	}

	std::cout << "|----------|----------|----------|----------|" << std::endl;
	std::cout << "\n" << std::endl;

	do {
		std::cout << "To find : ";
		this->_input_value(tmp);
		index = std::strtol(tmp.c_str(), &ptr, 10);
	
		if (index < 1 || index > BOOK_NBR || tmp.c_str() == ptr) {
			std::cout << ANSI_RED"Invalid/Wrong index !\n"ANSI_NONE << std::endl;
			continue ;
		}
		--index;
		if (this->_book[index].info_is_empty() == true) {
			std::cout << ANSI_RED"Contact : " << index + 1 << " is empty !\n" ANSI_NONE << std::endl;
			break ;
		}
		_print_search_contact(index);
		break ;
	} while (true);
}

void	PhoneBook::menu(void) const {
	std::string tmp;

	std::cout << "- Choose cmd -" << std::endl;
	std::cout << "[" ANSI_GREEN"ADD" ANSI_NONE "], ";
	std::cout << "[" ANSI_GREEN"SEARCH" ANSI_NONE"], ";
	std::cout << "[" ANSI_GREEN"EXIT" ANSI_NONE"]" << std::endl;
	std::cout << std::endl;
}
