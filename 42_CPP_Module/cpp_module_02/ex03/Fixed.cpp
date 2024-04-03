/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:33:45 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:13:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int const Fixed::_bits = 8;

/* 
** CONSTRUCTORS / DESTRUCTOR
*/
Fixed::Fixed(void) : _fixed(0) {
	return ;
}

Fixed::Fixed(int const i) : _fixed(i << Fixed::_bits) {
	return ;
}

Fixed::Fixed(float const f) : _fixed(roundf(f * ((float)(1 << Fixed::_bits)))) {
	return ;
}

Fixed::Fixed(Fixed const & src) {
	*this = src;
	return ;
}

Fixed::~Fixed(void) {
	return ;
}

/*
** MEMBERS
*/
int		Fixed::getRawBits(void) const {
	return this->_fixed;
}

void	Fixed::setRawBits(int const raw) {
	this->_fixed = raw;
}

float	Fixed::toFloat(void) const {
	return ((float)(this->_fixed)) / ((float)(1 << Fixed::_bits));
}

int		Fixed::toInt(void) const {
	return this->_fixed >> Fixed::_bits;
}

Fixed const & Fixed::min(Fixed const & a, Fixed const & b) {
	return (a.getRawBits() < b.getRawBits()) ? a : b;
}

Fixed const & Fixed::max(Fixed const & a, Fixed const & b) {
	return (a.getRawBits() > b.getRawBits()) ? a : b;
}

/*
** OPERATORS
*/
Fixed & Fixed::operator=(Fixed const & rhs) {
	if (this == &rhs) return *this;
	
	this->setRawBits(rhs.getRawBits());
	return *this;
}

bool Fixed::operator>(Fixed const & rhs) const { return (this->getRawBits() > rhs.getRawBits()) ? true : false; }
bool Fixed::operator<(Fixed const & rhs) const { return (this->getRawBits() < rhs.getRawBits()) ? true : false; }
bool Fixed::operator>=(Fixed const & rhs) const { return (this->getRawBits() >= rhs.getRawBits()) ? true : false; }
bool Fixed::operator<=(Fixed const & rhs) const { return (this->getRawBits() <= rhs.getRawBits()) ? true : false; }
bool Fixed::operator==(Fixed const & rhs) const { return (this->getRawBits() == rhs.getRawBits()) ? true : false; }
bool Fixed::operator!=(Fixed const & rhs) const { return (this->getRawBits() != rhs.getRawBits()) ? true : false; }

Fixed Fixed::operator+(Fixed const & rhs) const { return Fixed(this->toFloat() + rhs.toFloat());}
Fixed Fixed::operator-(Fixed const & rhs) const { return Fixed(this->toFloat() - rhs.toFloat());}
Fixed Fixed::operator*(Fixed const & rhs) const { return Fixed(this->toFloat() * rhs.toFloat());}
Fixed Fixed::operator/(Fixed const & rhs) const { return Fixed(this->toFloat() / rhs.toFloat());}

Fixed & Fixed::operator++(void) { /* PRE INCREMENT */
	++this->_fixed;
	return *this;
}

Fixed Fixed::operator++(int) { /* POST INCREMENT */
	Fixed tmp(*this);
	
	++this->_fixed;
	return tmp;
}

Fixed & Fixed::operator--(void) { /* PRE DECREMENT */
	--this->_fixed;
	return *this;
}

Fixed Fixed::operator--(int) { /* POST DECREMENT */
	Fixed tmp(*this);
	
	--this->_fixed;
	return tmp;
}

std::ostream & operator<<(std::ostream & o, Fixed const & i) {
	o << i.toFloat();
	return o;
}
