/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:32:24 by kaye              #+#    #+#             */
/*   Updated: 2021/08/02 19:13:27 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void) {
	Fixed		a;
	Fixed const	b(Fixed(5.05f) * Fixed(2));
	Fixed		c(1);
	Fixed		d(1.234f);

	std::cout << "\033[1;32mAssignment c to a\033[0m" << std::endl;
	std::cout << "a          : " << a << std::endl;
	std::cout << "c          : " << c << std::endl;
	std::cout << "a = c      : " << (a = c) << std::endl;
	std::cout << std::endl;
	
	std::cout << "\033[1;32mIncrement with a\033[0m" << std::endl;
	std::cout << "a          : " << a << std::endl;
	std::cout << "pre inc a  : " << ++a << std::endl;
	std::cout << "after inc a: " << a << std::endl;
	std::cout << "post inc a : " << a++ << std::endl;
	std::cout << "after inc a: " << a << std::endl;
	std::cout << std::endl;

	std::cout << "\033[1;32mDecrement with a\033[0m" << std::endl;
	std::cout << "a          : " << a << std::endl;
	std::cout << "pre dec a  : " << --a << std::endl;
	std::cout << "after dec a: " << a << std::endl;
	std::cout << "post dec a : " << a-- << std::endl;
	std::cout << "after dec a: " << a << std::endl;
	std::cout << std::endl;
	
	std::cout << "\033[1;32mCompare a and b\033[0m" << std::endl;
	std::cout << "a          : " << a << std::endl;
	std::cout << "b          : " << b << std::endl;
	std::cout << "a < b      : " << ((a < b) ? "true" : "false") << std::endl;
	std::cout << "a > b      : " << ((a > b) ? "true" : "false") << std::endl;
	std::cout << "a <= b     : " << ((a <= b) ? "true" : "false") << std::endl;
	std::cout << "a >= b     : " << ((a >= b) ? "true" : "false") << std::endl;
	std::cout << "a != b     : " << ((a != b) ? "true" : "false") << std::endl;
	std::cout << "a == b     : " << ((a == b) ? "true" : "false") << std::endl;
	std::cout << "max(a, b)  : " << Fixed::max(a, b) << std::endl;
	std::cout << "min(a, b)  : " << Fixed::min(a, b) << std::endl;
	std::cout << std::endl;
	
	std::cout << "\033[1;32mSome arithmetic with c and d\033[0m" << std::endl;
	std::cout << "c          : " << c << std::endl;
	std::cout << "d          : " << d << std::endl;
	std::cout << "c + d      = " << c + d << std::endl;
	std::cout << "c - d      = " << c - d << std::endl;
	std::cout << "c * d      = " << c * d << std::endl;
	std::cout << "c / d      = " << c / d << std::endl;
	return 0;
}
