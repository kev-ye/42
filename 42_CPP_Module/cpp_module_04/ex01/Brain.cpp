/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:05:18 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:17:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void) {
	const std::string brain[] = {
		"😀",
		"🤣",
		"😌",
		"😋",
		"🤓",
		"😔",
		"😫",
		"😡",
		"😨",
		"🤫",
		"😯",
		"😪"
	};

	std::cout << "\e[1;32mBrain\e[0m default constructor: ";
	for (int i = 0; i < NBR_IDEAS; i++) {
		this->_ideas[i] = brain[rand() % (sizeof(brain) / sizeof(std::string))];
		std::cout << this->_ideas[i];
	}
	std::cout << std::endl;
	return ;
}

Brain::Brain(Brain const & src) {
	std::cout << "\e[1;32mBrain\e[0m assignment constructor" << std::endl;
	for (int i = 0; i < NBR_IDEAS; i++)
			this->_ideas[i] = src._ideas[i];
	return ;
}

Brain::~Brain(void) {
	std::cout << "\e[1;32mBrain\e[0m destructor" << std::endl;
	return ;
}

std::string const &	Brain::getIdea(int idx) const {
	if (idx > NBR_IDEAS)
		idx = NBR_IDEAS;
	return this->_ideas[idx];
}

void	Brain::setIdea(int idx, std::string to_set) {
	this->_ideas[idx] = to_set;
}

Brain &	Brain::operator=(Brain const & rhs) {
	if (this == &rhs) return *this;

	for (int i = 0; i < NBR_IDEAS; i++)
		this->_ideas[i] = rhs._ideas[i];
	return *this;
}