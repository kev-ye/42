/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:06:02 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 19:48:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern(void) {}

Intern::~Intern(void) {}

Intern::Intern(Intern const & src) { *this = src; }

Intern &	Intern::operator=(Intern const & rhs) {
	if (this == &rhs) return *this;

	return *this;
}

Form	*Intern::makeForm(std::string const & formName, std::string const & target) {
	t_intern	intern[] = {
		{"shrubbery creation", &Intern::_CreateShrubberyCreationForm},
		{"robotomy request", &Intern::_CreateRobotomyRequestForm},
		{"presidential pardon", &Intern::_CreatePresidentialPardonForm}
	};

	for (int i = 0; i < 3; i++) {
		if (formName == intern[i].formName) {
			std::cout << "Intern creates [\e[1;32m"
				<< formName << "\e[0m]." << std::endl;
			return (this->*(intern[i].f))(target);
		}
	}
	std::cout << "Intern can't create [\e[1;31m"
				<< formName << "\e[0m]." << std::endl;
	return NULL;
}

Form	*Intern::_CreateShrubberyCreationForm(std::string const & target) {
	return new ShrubberyCreationForm(target);
}

Form	*Intern::_CreateRobotomyRequestForm(std::string const & target) {
	return new RobotomyRequestForm(target);
}

Form	*Intern::_CreatePresidentialPardonForm(std::string const & target) {
	return new PresidentialPardonForm(target);
}