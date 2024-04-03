/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:53:18 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 19:37:05 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

void	test1() {
	std::cout << "\e[1;32m- ShrubberyCreationForm -\e[0m" << std::endl;
	std::cout << "\e[1;33mUnsign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 100);
		Intern		someRandomIntern;
		Form		*scf;
	
		scf = someRandomIntern.makeForm("shrubbery creation", "shrubberycreationform");
		if (scf) {
			std::cout << *scf << std::endl;
			bureaucrat.executeForm(*scf);
			delete scf;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 100);
		Intern		someRandomIntern;
		Form		*scf;
	
		scf = someRandomIntern.makeForm("shrubbery creation", "shrubberycreationform");
		if (scf) {
			std::cout << *scf << std::endl;
			bureaucrat.signForm(*scf);
			bureaucrat.executeForm(*scf);
			delete scf;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign but exec grade too low case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 138);
		Intern		someRandomIntern;
		Form		*scf;
	
		scf = someRandomIntern.makeForm("shrubbery creation", "shrubberycreationform");
		if (scf){
			std::cout << *scf << std::endl;
			bureaucrat.signForm(*scf);
			bureaucrat.executeForm(*scf);
			delete scf;
		}
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
		Intern		someRandomIntern;
		Form		*rrf;
	
		rrf = someRandomIntern.makeForm("robotomy request", "robotomyrequestform");
		if (rrf) {
			std::cout << *rrf << std::endl;
			bureaucrat.executeForm(*rrf);
			delete rrf;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 25);
		Intern		someRandomIntern;
		Form		*rrf;
	
		rrf = someRandomIntern.makeForm("robotomy request", "robotomyrequestform");
		if (rrf) {
			std::cout << *rrf << std::endl;
			bureaucrat.signForm(*rrf);
			bureaucrat.executeForm(*rrf);
			delete rrf;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign but exec grade too low case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 50);
		Intern		someRandomIntern;
		Form		*rrf;
	
		rrf = someRandomIntern.makeForm("robotomy request", "robotomyrequestform");
		if (rrf) {
			std::cout << *rrf << std::endl;
			bureaucrat.signForm(*rrf);
			bureaucrat.executeForm(*rrf);
			delete rrf;
		}
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
		Intern		someRandomIntern;
		Form		*ppf;
	
		ppf = someRandomIntern.makeForm("presidential pardon", "presidentialpardonform");
		if (ppf) {
			bureaucrat.executeForm(*ppf);
			delete ppf;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 1);
		Intern		someRandomIntern;
		Form		*ppf;
	
		ppf = someRandomIntern.makeForm("presidential pardon", "presidentialpardonform");
		if (ppf) {
			bureaucrat.signForm(*ppf);
			bureaucrat.executeForm(*ppf);
			delete ppf;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\e[1;33mSign but exec grade too low case\e[0m" << std::endl;
	try {
		Bureaucrat	bureaucrat("bureaucreat", 10);
		Intern		someRandomIntern;
		Form		*ppf;
	
		ppf = someRandomIntern.makeForm("presidential pardon", "presidentialpardonform");
		if (ppf) {
			bureaucrat.signForm(*ppf);
			bureaucrat.executeForm(*ppf);
			delete ppf;
		}
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
#if defined(__APPLE__) && defined(__MACH__)
	/* show if leaks */
	std::cout << "\e[1;32m- if leaks ... -\e[0m\n" << std::endl;
	system("leaks intern");
#endif
	return (0);
}