/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:34:44 by kaye              #+#    #+#             */
/*   Updated: 2021/08/17 17:12:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) :
	Form("ShrubberyCreationForm", 145, 137),
	_target("Unknow") {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const & target) :
	Form("ShrubberyCreationForm", 145, 137),
	_target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & src) :
	Form(src),
	_target(src.getTarget()) { *this = src; }

ShrubberyCreationForm::~ShrubberyCreationForm(void) {}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & rhs) {
	if (this == &rhs) return *this;

	std::string	*tmp_target = (std::string *)&this->_target;

	*tmp_target = rhs.getTarget();
	return *this;
}

std::string const &	ShrubberyCreationForm::getTarget(void) const { return this->_target; }

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	if (this->getFormSign() == false)
		throw Form::NotSignedException();
	if (this->getExecGrade() < executor.getGrade())
		throw Form::GradeTooLowException();

	std::ifstream ifs("AsciiTree");
	if (!ifs.is_open())
		throw ShrubberyCreationForm::OpenFileFailedException();

	std::ofstream ofs((this->_target + "_shrubbery").c_str());
	if (!ofs.is_open())
		throw ShrubberyCreationForm::OpenFileFailedException();

	std::string contents;
	do {
		std::getline(ifs, contents);
		ofs << contents;

		if (ifs.eof() == true)
			break ;
		else
			ofs << std::endl;
	} while (true);
	
	ifs.close();
	ofs.close();
}

char const	*ShrubberyCreationForm::OpenFileFailedException::what() const throw() {
	return "\e[1;31mOpen File Failed!\e[0m";
}