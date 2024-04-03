/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:55:26 by kaye              #+#    #+#             */
/*   Updated: 2021/09/08 17:35:39 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>

class Span {
	public:
		Span(unsigned int n);
		Span(Span const & src);
		virtual ~Span(void);
	
		Span & operator=(Span const & rhs);

	private:
		Span(void);

	public:
		std::vector<int> const & getArray(void) const;
		void		setArray(int & arrayValue, int toSet);

		void	addNumber(int nbr);
		int		shortestSpan(void) const;
		int		longestSpan(void) const;

		void	generate(int unsigned range);

	private:
		std::vector<int>	_array;
		unsigned int		_n;
		unsigned int		_count;

	public:
		class CantAddNbrException : public std::exception {
			public:
				virtual char const * what() const throw();
		};
		class CantGetShortestSpanException : public std::exception {
			public:
				virtual char const * what() const throw();
		};
		class CantGetLongestSpanException : public std::exception {
			public:
				virtual char const * what() const throw();
		};
};

#endif