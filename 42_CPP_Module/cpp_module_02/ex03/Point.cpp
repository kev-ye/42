/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:56:48 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:14:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void) : _x(0), _y(0) {
	return ;
}

Point::Point(Fixed const x, Fixed const y) : _x(x), _y(y) {
	return ;
}

Point::Point(Point const & src) {
	*this = src;
	return ;
}

Point::~Point(void) {
	return ;
}

Point & Point::operator=(Point const & rhs) {
	if (this == &rhs) return *this;

	Fixed *x = (Fixed *)&this->_x;
	Fixed *y = (Fixed *)&this->_y;

	*x = rhs._x;
	*y = rhs._y;
	return *this;
}

Fixed Point::getX(void) const {
	return this->_x;
}

Fixed Point::getY(void) const {
	return this->_y;
}
