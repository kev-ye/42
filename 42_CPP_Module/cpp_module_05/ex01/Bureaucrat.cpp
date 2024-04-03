/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:54:17 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:03:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : _name("Unknow"), _note(150) {}

Bureaucrat::Bureaucrat(std::string const & name, int const note) : _name(name) {
	if (note < 1)
		throw Bureaucrat::GradeTooHighException();
	if (note > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_note = note;
}

Bureaucrat::Bureaucrat(Bureaucrat const & src) : _name(src.getName()) { *this = src; }

Bureaucrat::~Bureaucrat(void) {}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & rhs) {
	if (this == &rhs) return *this;

	std::string *tmp_name = (std::string *)&this->_name;

	*tmp_name = rhs.getName();
	this->_note = rhs.getGrade();
	return *this;
}

std::ostream & operator<<(std::ostream & o, Bureaucrat const & Bureaucrat) {
	o << "[\e[1;36m" << Bureaucrat.getName() << "\e[0m], bureaucrat grade [\e[1;36m"
		<< Bureaucrat.getGrade() << "\e[0m].";
	return o;
}

std::string const & Bureaucrat::getName(void) const { return this->_name; }

int const & 		Bureaucrat::getGrade(void) const { return this->_note; }

void	Bureaucrat::incGrade(void) {
	if (this->_note == 1)
		throw Bureaucrat::GradeTooHighException();
	--this->_note;
}

void	Bureaucrat::decGrade(void) {
	if (this->_note == 150)
		throw Bureaucrat::GradeTooLowException();
	++this->_note;
}

void	Bureaucrat::signForm(Form & form) {
	try {
		form.beSigned(*this);
		std::cout << "[\e[1;36m" << this->getName() << "\e[0m] signs [\e[1;36m" \
			<< form.getName() << "\e[0m]." << std::endl;
	}
	catch (std::exception & e) {
		std::cout << "[\e[1;36m" <<this->getName() << "\e[0m] cannot sign because " \
			<< e.what() << std::endl; 
	}
}

char const *	Bureaucrat::GradeTooHighException::what() const throw() {
	return "\e[1;31mGrate Too High!\e[0m";
}

char const *	Bureaucrat::GradeTooLowException::what() const throw() {
	return "\e[1;31mGrate Too Low!\e[0m";
}