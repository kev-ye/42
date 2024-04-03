/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:38:44 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:47:27 by kaye             ###   ########.fr       */
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
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I just love it!";
	std::cout << std::endl;
}

void	Karen::_info(void) {
	std::cout << "I cannot believe adding extra bacon cost more money. You don’t put enough! If you did I would not have to ask for it!";
	std::cout << std::endl;
}

void	Karen::_warning(void) {
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming here for years and you just started working here last month.";
	std::cout << std::endl;
}

void Karen::_error(void) {
	std::cout << "This is unacceptable, I want to speak to the manager now.";
	std::cout << std::endl;
}

void	Karen::complain(std::string level) {
	const std::string complain[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"};

	for (int i = 0; i < e_COMPLAIN; i++) {
		if (complain[i] == level) {
			std::cout << "[ " << complain[i] << " ]" << std::endl;
			(this->*_complain[i])();
			std::cout << std::endl;
			return ;
		}
	}
}
