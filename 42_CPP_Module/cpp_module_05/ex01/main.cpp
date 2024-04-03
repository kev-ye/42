/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:53:18 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 18:45:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

void test1(void) {
	std::cout << "\e[1;32m- Basic test -\e[0m" << std::endl;

	Bureaucrat bureaucrat1("bureaucrat1", 1);
	std::cout << "bureaucrat1: ";
	std::cout << bureaucrat1 << std::endl;

	Bureaucrat bureaucrat2("bureaucrat2", 150);
	std::cout << "bureaucrat2: ";
	std::cout << bureaucrat2 << std::endl;

	Form form1("form1", 100, 100);
	std::cout << "form1:       ";
	std::cout << form1 << std::endl;

	std::cout << "B1 sign F1:  ";
	bureaucrat1.signForm(form1);

	std::cout << "B2 sign F1:  ";
	bureaucrat2.signForm(form1);

	std::cout << std::endl;
}

void test2(void) {
	std::cout << "\e[1;32m- Assignment test -\e[0m" << std::endl;

	Bureaucrat bureaucrat1("bureaucrat1", 100);
	std::cout << "bureaucrat1: ";
	std::cout << bureaucrat1 << std::endl;

	Form form1("form1", 150, 150);
	std::cout << "form1:       ";
	std::cout << form1 << std::endl;

	Form form2("form2", 1, 1);
	std::cout << "form2:       ";
	std::cout << form2 << std::endl;

	std::cout << "B1 sign F1:  ";
	bureaucrat1.signForm(form1);

	form1 = form2;

	std::cout << "F1 = F2:     ";
	bureaucrat1.signForm(form1);

	std::cout << std::endl;
}

void test3(void) {
	std::cout << "\e[1;32m- Exception true case test -\e[0m" << std::endl;

	try {
		Bureaucrat bureaucrat1("bureaucrat1", 1);
		std::cout << "bureaucrat1: ";
		std::cout << bureaucrat1 << std::endl;

		Form form1("form1", 100, 100);
		std::cout << "form1:       ";
		std::cout << form1 << std::endl;

		std::cout << "B1 sign F1:  ";
		bureaucrat1.signForm(form1);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;
}

void test4(void) {
	std::cout << "\e[1;32m- Exception false case test -\e[0m" << std::endl;

	try {
		Form form1("form1", -1, -1);
	}
	catch (std::exception & e) {
		std::cout << "\"form1\", -1, -1:         ";
		std::cerr << e.what() << std::endl;
	}

	try {
		Form form2("form2", -1, 1);
	}
	catch (std::exception & e) {
		std::cout << "\"form2\", -1, 100:        ";
		std::cerr << e.what() << std::endl;
	}

	try {
		Form form3("form3", 151, 151);
	}
	catch (std::exception & e) {
		std::cout << "\"form3\", 151, 151:       ";
		std::cerr << e.what() << std::endl;
	}

	try {
		Form form4("form4", 1, 151);
	}
	catch (std::exception & e) {
		std::cout << "\"form4\", 1, 151:         ";
		std::cerr << e.what() << std::endl;
	}

	try {
		Bureaucrat bureaucrat("bureaucrat", 150);
		Form form("form", 100, 100);

		std::cout << "B(150), F(100):beSigned: ";
		form.beSigned(bureaucrat);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;
}

int main() {
	test1();
	test2();
	test3();
	test4();
	return (0);
}