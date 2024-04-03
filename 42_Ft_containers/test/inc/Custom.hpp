/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Custom.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:47:46 by kaye              #+#    #+#             */
/*   Updated: 2021/10/10 18:58:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_HPP
# define CUSTOM_HPP

#include <string>

class Custom {
	public:
		Custom(void) {}
		Custom(Custom const & src) : _i(src._i), _str(src._str) {}
		Custom(int const i, std::string const & str) : _i(i), _str(str) {}
		~Custom(void) {}

		Custom & operator=(Custom const & rhs) {
			if (this == &rhs) return *this;

			_i = rhs._i;
			_str = rhs._str;
			return *this;
		}

		int getI(void) const { return _i; };
		std::string getStr(void) const { return _str; };

	private:
		int _i;
		std::string _str;
};

bool operator== (Custom const & lhs, Custom const & rhs) {
	if (lhs.getI() == rhs.getI())
		return true;
	return false;
}

bool operator!= (Custom const & lhs, Custom const & rhs) {
	if (lhs.getI() != rhs.getI())
		return true;
	return false;
}

bool operator< (Custom const & lhs, Custom const & rhs) {
	if (lhs.getI() < rhs.getI())
		return true;
	return false;
}

bool operator<= (Custom const &lhs, Custom const & rhs) {
	if (lhs.getI() <= rhs.getI())
		return true;
	return false;
}

bool operator> (Custom const & lhs, Custom const & rhs) {
	if (lhs.getI() > rhs.getI())
		return true;
	return false;
}

bool operator>= (Custom const &lhs, Custom const & rhs) {
	if (lhs.getI() >= rhs.getI())
		return true;
	return false;
}

#endif