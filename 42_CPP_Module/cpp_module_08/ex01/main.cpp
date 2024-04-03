/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:55:10 by kaye              #+#    #+#             */
/*   Updated: 2021/08/24 13:02:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

void	print(int i) { std::cout << ' ' << i; }

int		RandomNumber(void) { return std::rand() % 100; }

void	test1() {
	std::cout << "\e[1;32m- Baisc test -\e[0m" << std::endl;
	Span sp = Span(5);

	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "\e[1;35mInit:\e[0m ";
	std::for_each(sp.getArray().begin(), sp.getArray().end(), print);
	std::cout << std::endl;

	std::cout << "\e[1;34mShortest span:\e[0m " << sp.shortestSpan() << std::endl;
	std::cout << "\e[1;36mLongest span:\e[0m " << sp.longestSpan() << std::endl;

	std::cout << std::endl;
}

void	test2() {
	std::cout << "\e[1;32m- With 10000 random number -\e[0m" << std::endl;
	Span sp = Span(10000);
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	sp.generate(10000);

	std::cout << "\e[1;35mInit:\e[0m ";
	std::cout << sp.getArray()[0] << " [...] " << sp.getArray()[9999] << " (remove the comment, if you want know the detail ...)";
	// std::for_each(sp.getArray().begin(), sp.getArray().end(), print);
	std::cout << std::endl;

	std::cout << "\e[1;34mShortest span:\e[0m " << sp.shortestSpan() << std::endl;
	std::cout << "\e[1;36mLongest span:\e[0m " << sp.longestSpan() << std::endl;

	std::cout << std::endl;
}

void	test3() {
	std::cout << "\e[1;32m- Error case -\e[0m" << std::endl;
	Span sp1 = Span(10);
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	sp1.generate(10);

	try {
		std::cout << "\e[1;35mInit:\e[0m ";
		std::for_each(sp1.getArray().begin(), sp1.getArray().end(), print);
		std::cout << std::endl;

		std::cout << "range of array is [10], we already have 10 number and we try add more number... " << std::endl;
		sp1.addNumber(10);
	}
	catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	Span sp2 = Span(1);
	sp2.generate(1);

	try {
		std::cout << "\e[1;35mInit:\e[0m ";
		std::for_each(sp2.getArray().begin(), sp2.getArray().end(), print);
		std::cout << std::endl;

		std::cout << "\e[1;34mShortest span:\e[0m " << sp2.shortestSpan() << std::endl;
	}
	catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	Span sp3 = Span(1);
	sp3.generate(1);

	try {
		std::cout << "\e[1;35mInit:\e[0m ";
		std::for_each(sp3.getArray().begin(), sp3.getArray().end(), print);
		std::cout << std::endl;

		std::cout << "\e[1;34mLongest span:\e[0m " << sp3.longestSpan() << std::endl;
	}
	catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

int main() {
	test1();
	test2();
	test3();
	return 0;
}
