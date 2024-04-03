/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:22:39 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:04:28 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void) :
	_name("Unknow"),
	_signGrade(150),
	_execGrade(150),
	_formSign(false) {}

Form::Form(std::string const & name, int const signGrade, int const execGrade) :
	_name(name),
	_signGrade(signGrade),
	_execGrade(execGrade),
	_formSign(false) {
	if (signGrade < 1 || execGrade < 1)
		throw Form::GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(Form const & src) :
	_name(src.getName()),
	_signGrade(src.getSignGrade()),
	_execGrade(src.getExecGrade()),
	_formSign(src.getFormSign()) {
	*this = src;
}

Form::~Form(void) {}

Form &	Form::operator=(Form const & rhs) {
	if (this == &rhs) return *this;

	std::string	*tmp_name = (std::string *)&this->_name;
	int			*tmp_signGrade = (int *)&this->_signGrade;
	int			*tmp_execGrade = (int *)&this->_execGrade;

	*tmp_name = rhs.getName();
	*tmp_signGrade = rhs.getSignGrade();
	*tmp_execGrade = rhs.getExecGrade();
	this->_formSign = rhs.getFormSign();
	return *this;
}

std::ostream & operator<<(std::ostream & o, Form const & form) {
	o << "[\e[1;36m" << form.getName() << "\e[0m], Form sign grade [\e[1;36m" \
		<< form.getSignGrade() << "\e[0m] and Form exec grade [\e[1;36m" \
		<< form.getExecGrade() << "\e[0m], form is [\e[1;36m" \
		<< (form.getFormSign()? "signed" : "unsigned") << "\e[0m].";
	return o;
}

std::string const &	Form::getName(void) const { return this->_name; }
int const &			Form::getSignGrade(void) const { return this->_signGrade; }
int const &			Form::getExecGrade(void) const { return this->_execGrade; }
bool const &		Form::getFormSign(void) const { return this->_formSign; }

void				Form::setFormSign(bool sign) { this->_formSign = sign; }

void	Form::beSigned(Bureaucrat const & Bureaucrat) {
	if (this->getSignGrade() < Bureaucrat.getGrade())
		throw Form::GradeTooLowException();
	this->setFormSign(true);
}

char const	*Form::GradeTooHighException::what() const throw() {
	return "\e[1;31mGrade Too High!\e[0m";
}

char const	*Form::GradeTooLowException::what() const throw() {
	return "\e[1;31mGrade Too Low!\e[0m";
}

char const	*Form::NotSignedException::what() const throw() {
	return "\e[1;31mForm Is Not Signed!\e[0m";
}