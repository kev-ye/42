/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:34:27 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 16:27:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) :
	Form("PresidentialPardonForm", 25, 5),
	_target("Unknow") {}

PresidentialPardonForm::PresidentialPardonForm(std::string const & target) :
	Form("PresidentialPardonForm", 25, 5),
	_target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & src) :
	Form(src),
	_target(src.getTarget()) { *this = src; }

PresidentialPardonForm::~PresidentialPardonForm(void) {}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & rhs) {
	if (this == &rhs) return *this;

	std::string *tmp_target = (std::string *)&this->_target;

	*tmp_target = rhs.getTarget();
	return *this;
}

std::string const & PresidentialPardonForm::getTarget(void) const { return this->_target; }

void	PresidentialPardonForm::execute(Bureaucrat const & executor) const {
	if (this->getFormSign() == false)
		throw Form::NotSignedException();
	if (this->getExecGrade() < executor.getGrade())
		throw Form::GradeTooLowException();
	std::cout << "[\e[1;32m" << this->_target
		<< "\e[0m] forgiven by Zafod Beeblebrox." << std::endl;
}