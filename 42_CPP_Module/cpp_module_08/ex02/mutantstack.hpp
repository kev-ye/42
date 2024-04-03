/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:03:04 by kaye              #+#    #+#             */
/*   Updated: 2021/09/08 17:19:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <deque>

template< typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
	public:
		MutantStack(void) : std::stack<T, Container>() {};
		MutantStack(MutantStack const & src) { *this = src; }
		virtual ~MutantStack(void) {};

		MutantStack & operator=(MutantStack const & rhs) {
			if (this == &rhs) return *this;

			std::stack<T, Container>::operator=(rhs);
			return *this;
		}

		/* typedef creates an alias for an existing type, and typename tells the compiler that std[...]::iterator is a type and not a member. */
		typedef typename std::stack<T, Container>::container_type::iterator iterator;
		typedef typename std::stack<T, Container>::container_type::reverse_iterator reverse_iterator;
	
	public:
		iterator begin() { return std::stack<T, Container>::c.begin();};
		iterator end() { return std::stack<T, Container>::c.end(); };

		reverse_iterator rbegin() { return std::stack<T, Container>::c.rbegin();};
		reverse_iterator rend() { return std::stack<T, Container>::c.rend(); };
};

#endif