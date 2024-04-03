/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:01:07 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 15:22:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data(void) :
	_c('0'),
	_i(0),
	_str("Unknow") {}

Data::Data(char const c, int const i, std::string const & str) :
	_c(c),
	_i(i),
	_str(str) {}

Data::Data(Data const & src) {
	this->_c = src._c;
	this->_i = src._i;
	this->_str = src._str;
}

Data::~Data() {}

Data & Data::operator=(Data const & rhs) {
	if (this == &rhs) return *this;

	this->_c = rhs._c;
	this->_i = rhs._i;
	this->_str = rhs._str;
	return *this;
}

char const &		Data::getC(void) const { return this->_c; }
int const &			Data::getI(void) const { return this->_i; }
std::string const &	Data::getStr(void) const { return this->_str; }

uintptr_t	serialize(Data *ptr) { return reinterpret_cast<uintptr_t>(ptr); }

Data	*deserialize(uintptr_t raw) { return reinterpret_cast<Data *>(raw); }