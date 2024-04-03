/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:57:14 by kaye              #+#    #+#             */
/*   Updated: 2021/08/01 19:50:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iomanip>

#define TESTS 7

int main() {
	{	// MAIN 1
		Point 		a;
		Point 		b(1, 2);
		Point const c(b);
		Point 		d;

		d = c;
		std::cout << "\033[1;32mAssignment\033[0m" << std::endl;
		std::cout << "a.x      : " << a.getX().toFloat() << std::endl;
		std::cout << "a.y      : " << a.getY().toFloat() << std::endl;

		std::cout << "b.x      : " << b.getX().toFloat() << std::endl;
		std::cout << "b.y      : " << b.getY().toFloat() << std::endl;

		std::cout << "c(b).x   : " << c.getX().toFloat() << std::endl;
		std::cout << "c(b).y   : " << c.getY().toFloat() << std::endl;

		std::cout << "(d = c).x: " << d.getX().toFloat() << std::endl;
		std::cout << "(d = c).y: " << d.getY().toFloat() << std::endl;
		std::cout << std::endl;
	}
	{	// MAIN 2
		Point const 	a(0, 0);
		Point const 	b(10, 30);
		Point const 	c(20, 0);
		Point			*points = new Point[TESTS];

		points[0] = Point(10, 15);
		points[1] = Point(30, 15);
		points[2] = Point(0, 0);
		points[3] = Point(10, 30);
		points[4] = Point(20, 0);
		points[5] = Point(15, 2);
		points[6] = Point(10, 29);

		std::cout << "\033[1;32mIs inside triangle\033[0m" << std::endl;
		std::cout << "a : " << "(" << a.getX().toFloat() << ", " << a.getY().toFloat() << ")" << std::endl;
		std::cout << "b : " << "(" << b.getX().toFloat() << ", " << b.getY().toFloat() << ")" << std::endl;
		std::cout << "c : " << "(" << c.getX().toFloat() << ", " << c.getY().toFloat() << ")" << std::endl;
		std::cout << std::endl;
	
		for (int i = 0; i < TESTS; ++i) {
			std::cout << "(" << points[i].getX() << ", " << points[i].getY() << ") ";
			std::cout << "is inside: " << (bsp(a, b, c, points[i])? "\033[1;32mtrue\033[0m" : "\033[1;31mfalse\033[0m") << std::endl;
		}

		delete [] points;
	}
	return 0;
}