/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:38:51 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 19:17:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include <iostream>
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define FORM_NBR

class Intern {
	public:
		Intern(void);
		Intern(Intern const & src);
		virtual ~Intern(void);

		Intern &	operator=(Intern const & rhs);

	public:
		Form	*makeForm(std::string const & formName, std::string const & target);

	private:
		Form	*_CreateShrubberyCreationForm(std::string const &);
		Form	*_CreateRobotomyRequestForm(std::string const &);
		Form	*_CreatePresidentialPardonForm(std::string const &);

		typedef Form *(Intern::*func)(std::string const &);
		typedef	struct s_intern {
			std::string formName;
			func const f;
		}	t_intern;
};

#endif