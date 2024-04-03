/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:53:18 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 18:45:03 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

void	test1() {
	std::cout << "\e[1;32m- ShrubberyCreationForm -\e[0m" << std::endl;
	std::cout << "\e[1;33mUnsign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 100);
		ShrubberyCreationForm shrubberycreationform("scf");
	
		std::cout << shrubberycreationform << std::endl;
		bureaucrat.executeForm(shrubberycreationform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 100);
		ShrubberyCreationForm shrubberycreationform("scf");
	
		std::cout << shrubberycreationform << std::endl;
		bureaucrat.signForm(shrubberycreationform);
		bureaucrat.executeForm(shrubberycreationform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign but exec grade too low case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 138);
		ShrubberyCreationForm shrubberycreationform("scf");
	
		std::cout << shrubberycreationform << std::endl;
		bureaucrat.signForm(shrubberycreationform);
		bureaucrat.executeForm(shrubberycreationform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;
}

void	test2() {
	std::cout << "\e[1;32m- RobotomyRequestForm -\e[0m" << std::endl;
	std::cout << "\e[1;33mUnsign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 25);
		RobotomyRequestForm robotomyrequestform("rrf");
	
		std::cout << robotomyrequestform << std::endl;
		bureaucrat.executeForm(robotomyrequestform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 25);
		RobotomyRequestForm robotomyrequestform("rrf");
	
		std::cout << robotomyrequestform << std::endl;
		bureaucrat.signForm(robotomyrequestform);
		bureaucrat.executeForm(robotomyrequestform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign but exec grade too low case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 50);
		RobotomyRequestForm robotomyrequestform("rrf");
	
		std::cout << robotomyrequestform << std::endl;
		bureaucrat.signForm(robotomyrequestform);
		bureaucrat.executeForm(robotomyrequestform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;
}

void	test3() {
	std::cout << "\e[1;32m- PresidentialPardonForm -\e[0m" << std::endl;
	std::cout << "\e[1;33mUnsign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 1);
		PresidentialPardonForm presidentialpardonform("ppf");
	
		std::cout << presidentialpardonform << std::endl;
		bureaucrat.executeForm(presidentialpardonform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 1);
		PresidentialPardonForm presidentialpardonform("ppf");
	
		std::cout << presidentialpardonform << std::endl;
		bureaucrat.signForm(presidentialpardonform);
		bureaucrat.executeForm(presidentialpardonform);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign but exec grade too low case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 10);
		PresidentialPardonForm presidentialpardonform("ppf");
	
		std::cout << presidentialpardonform << std::endl;
		bureaucrat.signForm(presidentialpardonform);
		bureaucrat.executeForm(presidentialpardonform);
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
	return (0);
}