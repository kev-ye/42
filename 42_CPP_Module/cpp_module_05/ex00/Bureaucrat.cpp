/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:54:17 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:03:19 by kaye             ###   ########.fr       */
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

std::ostream & operator<<(std::ostream & o, Bureaucrat const & i) {
	o << "[\e[1;36m" << i.getName() << "\e[0m], bureaucrat grade [\e[1;36m"
		<< i.getGrade() << "\e[0m].";
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

char const *	Bureaucrat::GradeTooHighException::what() const throw() {
	return "\e[1;31mGrate Too High Exception!\e[0m";
}

char const *	Bureaucrat::GradeTooLowException::what() const throw() {
	return "\e[1;31mGrate Too Low Exception!\e[0m";
}