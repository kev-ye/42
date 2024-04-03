/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:26:00 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:47:49 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

Karen::Karen(void) {
	_complain[e_DEBUG] = &Karen::_debug;
	_complain[e_INFO] = &Karen::_info;
	_complain[e_WARNING] = &Karen::_warning;
	_complain[e_ERROR] = &Karen::_error;
	return ;
}

Karen::~Karen(void) {
	return ;
}

void	Karen::_debug(void) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger.\n" \
		<< "I just love it!\n";
	std::cout << std::endl;
}

void	Karen::_info(void) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon cost more money.\n" \
		<< "You don’t put enough!\n" \
		<< "If you did I would not have to ask for it!\n";
	std::cout << std::endl;
}

void	Karen::_warning(void) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free.\n"
		<< "I’ve been coming here for years and you just started working here last month.\n";
	std::cout << std::endl;
}

void Karen::_error(void) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable, I want to speak to the manager now.\n";
	std::cout << std::endl;
}

void	Karen::complain(std::string level) {
	const std::string complain[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"};
	int i = 0;

	for (; i < e_COMPLAIN && complain[i] != level; i++);

	switch (i) {
		case e_DEBUG:
			(this->*_complain[i++])();

		case e_INFO:
			(this->*_complain[i++])();
		
		case e_WARNING:
			(this->*_complain[i++])();

		case e_ERROR:
			(this->*_complain[i])();
			break;
		
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break;
	}
}
