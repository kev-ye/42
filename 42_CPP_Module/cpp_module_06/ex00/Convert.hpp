/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:51:00 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 17:15:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

#include <iostream>
#include <iomanip>
#include <exception>
#include <cstdlib>
#include <stdint.h>

class Convert {
	public:
		Convert(void);
		Convert(std::string const & str);
		Convert(Convert const & src);
		virtual ~Convert(void);

		Convert &	operator=(Convert const &rhs);

		operator char();
		operator int();
		operator float();
		operator double();
	
	public:
		std::string const &	getStr(void) const;

		void	display(void);

		void	printChar(void);
		void	printInt(void);
		void	printFloat(void);
		void	printDouble(void);

	private:
		std::string _str;

	public:
		class CantDisplayException : public std::exception {
			public:
				virtual char const * what() const throw();
		};
		class CantConvertException : public std::exception {
			public:
				virtual char const * what() const throw();
		};
};

#endif