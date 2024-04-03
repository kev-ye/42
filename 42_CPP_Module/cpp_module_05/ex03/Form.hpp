/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:22:41 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 13:50:47 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	public:
		Form(void);
		Form(std::string const & name, int const signGrade, int const execGrade);
		Form(Form const & src);
		virtual ~Form(void);

		Form &	operator=(Form const & rhs);

	public:
		std::string const &	getName(void) const;
		int const &			getSignGrade(void) const;
		int const &			getExecGrade(void) const;
		bool const &		getFormSign(void) const;
		void				setFormSign(bool sign);

		void	beSigned(Bureaucrat const & Bureaucrat);

		virtual void execute(Bureaucrat const & executor) const = 0;

	private:
		std::string const	_name;
		int const			_signGrade;
		int const			_execGrade;
		bool				_formSign;

	public:
		class GradeTooHighException : public std::exception {
			public:
				virtual char const	*what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual char const	*what() const throw();
		};
		class NotSignedException : public std::exception {
			public:
				virtual char const	*what() const throw();
		};
};

std::ostream &	operator<<(std::ostream & o, Form const & form);

#endif