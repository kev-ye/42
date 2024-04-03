/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:50:57 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 13:00:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert(void) : _str("0") {}

Convert::Convert(std::string const & str) : _str(str) {}

Convert::Convert(Convert const & src) { *this = src; }

Convert::~Convert(void) {}

Convert &	Convert::operator=(Convert const & rhs) {
	if (this == &rhs) return *this;

	this->_str = rhs._str;
	return *this;
}

Convert::operator char() {
	std::string	str = this->getStr();
	char 		*ptr = NULL;
	long		c = 0;

	c = strtol(str.c_str(), &ptr, 10);
	if (str.c_str() == ptr)
		throw Convert::CantConvertException();
	if (c < 32 || c > 126)
		throw Convert::CantDisplayException();
	return static_cast<char>(c);
}

Convert::operator int() {
	std::string str = this->getStr();
	char		*ptr = NULL;
	long		i = 0;

	i = strtol(str.c_str(), &ptr, 10);
	if (str.c_str() == ptr || i > INT32_MAX || i < INT32_MIN)
		throw Convert::CantConvertException();
	return static_cast<int>(i);
}

Convert::operator float() {
	std::string str = this->getStr();
	char		*ptr = NULL;
	float		f = 0.0f;

	f = strtof(str.c_str(), &ptr);
	if (str.c_str() == ptr)
		throw Convert::CantConvertException();
	return f;
}

Convert::operator double() {
	std::string str = this->getStr();
	char		*ptr = NULL;
	double		d = 0.0;

	d = strtod(str.c_str(), &ptr);
	if (str.c_str() == ptr)
		throw Convert::CantConvertException();
	return d;
}

void	Convert::display(void) {
	this->printChar();
	this->printInt();
	this->printFloat();
	this->printDouble();
}

void	Convert::printChar(void) {
	try {
		std::cout << "\e[1;32mchar:\e[0m ";
		char c = static_cast<char>(*this);
		std::cout << "'" << c << "'" << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void	Convert::printInt(void) {
	try {
		std::cout << "\e[1;33mint:\e[0m ";
		int i = static_cast<int>(*this);
		std::cout << i << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void	Convert::printFloat(void) {
	try {
		std::cout << "\e[1;34mfloat:\e[0m ";
		float f = static_cast<float>(*this);
		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(1)
			<< f << "f" << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void	Convert::printDouble(void) {
	try {
		std::cout << "\e[1;36mdouble:\e[0m ";
		double d = static_cast<double>(*this);
		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(1)
			<< d << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

std::string const &	Convert::getStr(void) const { return this->_str; }

char const *Convert::CantDisplayException::what() const throw() {
	return "Non displayable";
}

char const *Convert::CantConvertException::what() const throw() {
	return "impossible";
}