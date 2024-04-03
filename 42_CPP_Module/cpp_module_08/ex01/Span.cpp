/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:55:22 by kaye              #+#    #+#             */
/*   Updated: 2021/08/24 13:00:33 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(void) {}

Span::Span(unsigned int n) :
	_array(n, 0),
	_n(n),
	_count(0) {}

Span::Span(Span const & src) {
	*this = src;
}

Span::~Span(void) {}

Span &	Span::operator=(Span const & rhs) {
	if (this == & rhs) return *this;

	this->_n = rhs._n;
	this->_count = rhs._count;
	this->_array = rhs.getArray();
	return *this;
}

std::vector<int> const &	Span::getArray(void) const { return this->_array; }
void		Span::setArray(int & arrayValue, int toSet) { arrayValue = toSet; }

void	Span::addNumber(int nbr) {
	if (this->_count >= this->_n) throw CantAddNbrException();

	this->setArray(this->_array[this->_count], nbr);
	++this->_count;
}

int		Span::shortestSpan(void) const {
	if (this->_count <= 1) throw Span::CantGetShortestSpanException();

	std::vector<int>::const_iterator max = std::max_element(this->_array.begin(), this->_array.begin() + this->_count);
	std::vector<int>::const_iterator min = std::min_element(this->_array.begin(), this->_array.begin() + this->_count);
	int spanMin = *max - *min;

	std::vector<int> tmp = this->_array;
	std::sort(tmp.begin(), tmp.begin() + this->_count);
	std::reverse(tmp.begin(), tmp.begin() + this->_count);

	for (unsigned int i = 0; i < this->_count - 1; i++)
			if (tmp[i] - tmp[i + 1] < spanMin)
				spanMin = tmp[i] - tmp[i + 1];
	return spanMin;
}

int		Span::longestSpan(void) const {
	if (this->_count <= 1) throw Span::CantGetLongestSpanException();

	std::vector<int>::const_iterator max = std::max_element(this->_array.begin(), this->_array.begin() + this->_count);
	std::vector<int>::const_iterator min = std::min_element(this->_array.begin(), this->_array.begin() + this->_count);
	return *max - *min;
}

void	Span::generate(unsigned int range) {
	if (range > this->_n || this->_count >= this->_n) throw CantAddNbrException();

	for (unsigned int i = this->_count; i < range && this->_count < this->_n; i++) {
		this->_array[i] = rand() % 10000;
		++this->_count;
	}
}

char const *Span::CantAddNbrException::what() const throw() { return "\e[1;31mCan't add number!\e[0m"; }
char const *Span::CantGetShortestSpanException::what() const throw() { return "\e[1;31mCan't get shortest span number!\e[0m"; }
char const *Span::CantGetLongestSpanException::what() const throw() { return "\e[1;31mCan't get longest span number!\e[0m"; }