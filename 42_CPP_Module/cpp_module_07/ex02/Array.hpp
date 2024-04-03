/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 16:17:54 by kaye              #+#    #+#             */
/*   Updated: 2021/08/20 18:35:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>
#include <exception>

template< typename T >
class Array {
	public:
		Array(void) :
			_array(new T[0]),
			_size(0) {}
		Array(unsigned int n) :
			_array(new T[n]),
			_size(n) {}
		Array(Array const & src) {
			this->_array = new T[src.size()];
			this->_size = src.size();
			for (unsigned int i = 0; i < this->size(); i++)
				this->_array[i] = src._array[i];
		}
		virtual ~Array(void) { if (this->_array) delete [] this->_array; }

		Array &	operator=(Array const & rhs) {
			if (this == &rhs) return *this;

			if (this->_array)
				delete [] this->_array;
			this->_array = new T[rhs.size()];
			this->_size = rhs.size();
			for (unsigned int i = 0; i < this->size(); i++)
				this->_array[i] = rhs._array[i];
			return *this;
		}

		T & operator[](unsigned int idx) {
			if (idx >= this->_size)
				throw std::exception();
			return this->_array[idx];
		}

	public:
		unsigned int const &	size(void) const { return this->_size; }

	private:
		T *_array;
		unsigned int _size;
};

#endif