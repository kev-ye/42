/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:50:38 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 17:02:36 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base(void) {}

Base	*generate(void) {
	int i = rand() % 3;

	if (i == 0)
		return new A();
	else if (i == 1)
		return new B();
	else
		return new C();
}

void	identify_from_pointer(Base * p) {
	if (dynamic_cast<A *>(p) != NULL)
		std::cout << "A";
	if (dynamic_cast<B *>(p) != NULL)
		std::cout << "B";
	if (dynamic_cast<C *>(p) != NULL)
		std::cout << "C";
}

void	identify_from_reference(Base & p) {
	try {
		A &a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "A";
	}
	catch (std::bad_cast & e) {}

	try {
		B &b = dynamic_cast<B &>(p);
		(void)b;
		std::cout << "B";
	}
	catch (std::bad_cast & e) {}

	try {
		C &c = dynamic_cast<C &>(p);
		(void)c;
		std::cout << "C";
	}
	catch (std::bad_cast & e) {}
}