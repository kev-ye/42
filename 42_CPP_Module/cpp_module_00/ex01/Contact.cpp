/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:34:21 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:38:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact (void) {
	return ;
}

Contact::~Contact (void) {
	return ;
}

void	Contact::info_clean(void) {
	for (int i = 0; i < INFO_NBR; i++)
		this->_info[i].clear();
}

bool	Contact::info_is_empty(void) const {
	for (int i = 0; i < INFO_NBR; i++) {
		if (this->_info[i].empty() == false)
			return (false);
	}
	return (true);
}

std::string Contact::get_info(int info_i) const {
	return this->_info[info_i];
}

void		Contact::set_info(std::string to_set, int info_i) {
	this->_info[info_i] = to_set;
}