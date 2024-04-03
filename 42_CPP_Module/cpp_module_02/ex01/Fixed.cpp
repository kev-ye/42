/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 17:36:06 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:12:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int const Fixed::_bits = 8;

/*
** CONSTRUCTORS / DESTRUCTOR
*/
Fixed::Fixed(void) : _fixed(0) {
	std::cout << "Default constructor called" << std::endl;
	return ;
}

Fixed::Fixed(int const i) : _fixed(i << Fixed::_bits) {
	std::cout << "Int constructor called" << std::endl;
	return ;
}

Fixed::Fixed(float const f) : _fixed(roundf(f * ((float)(1 << Fixed::_bits)))) {
	std::cout << "Float constructor called" << std::endl;
	return ;
}

Fixed::Fixed(Fixed const & src) {
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
	return ;
}

Fixed::~Fixed(void) {
	std::cout << "Destructor called" << std::endl;
	return ;
}

/*
** MEMBERS
*/
int	Fixed::getRawBits(void) const {
	return 	this->_fixed;
}

void	Fixed::setRawBits(int const raw) {
	this->_fixed = raw;
}

float	Fixed::toFloat(void) const {
	return ((float)(this->_fixed)) / ((float)(1 << Fixed::_bits));
}

int Fixed::toInt(void) const {
	return this->_fixed >> Fixed::_bits;
}

/*
** OPERATORS
*/
Fixed & Fixed::operator=(Fixed const & rhs) {
	std::cout << "Assignation operator called" << std::endl;
	if (this == &rhs) return *this;
	
	this->setRawBits(rhs.getRawBits());
	return *this;
}

std::ostream & operator<<(std::ostream & o, Fixed const & i) {
	o << i.toFloat();
	return o;
}