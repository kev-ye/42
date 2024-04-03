/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:34:37 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 16:23:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void) :
	Form("RobotomyRequestForm", 72, 45),
	_target("Unknow") {}

RobotomyRequestForm::RobotomyRequestForm(std::string const & target) :
	Form("RobotomyRequestForm", 72, 45),
	_target(target) {}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & src) :
	Form(src),
	_target(src.getTarget()) { *this = src; }

RobotomyRequestForm::~RobotomyRequestForm(void) {}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & rhs) {
	if (this == &rhs) return *this;

	std::string *tmp_target = (std::string *)&this->_target;

	*tmp_target = rhs.getTarget();
	return *this;
}

std::string const &	RobotomyRequestForm::getTarget(void) const { return this->_target; }

void	RobotomyRequestForm::execute(Bureaucrat const &	executor) const {
	if (this->getFormSign() == false)
		throw Form::NotSignedException();
	if (this->getExecGrade() < executor.getGrade())
		throw Form::GradeTooLowException();
	std::cout << "* \e[1;31mNOISE\e[0m * Bzzzzzzz Drrrrrrrr Bzzzzzz ..." << std::endl;
	srand(time(NULL));
	if (rand() % 2 == true)
		std::cout << "[\e[1;32m" << this->_target
			<< "\e[0m] has been robotomized!" << std::endl;
	else
		std::cout << "[\e[1;31m" << this->_target
			<< "\e[0m] robotomize failed!" << std::endl;
}