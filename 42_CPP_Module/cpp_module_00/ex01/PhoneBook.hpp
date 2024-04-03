/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:40:57 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:44:13 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOK_HPP
# define BOOK_HPP

#include "Contact.hpp"

#define ANSI_GREEN "\033[1;32m"
#define ANSI_RED "\033[1;31m"
#define ANSI_NONE "\033[0m"

#define BOOK_NBR 8

class PhoneBook {
	public:
		PhoneBook(void);
		~PhoneBook(void);
		
	public:
		void	menu(void) const;
		void	add_contact(void);
		void	search_contact(void) const;
		void	exit(void) const;

	private:
		int		_book_i;
		Contact _book[BOOK_NBR];

	private:
		void	_input_value(std::string &tmp) const;
		void	_show_search_contact_line(int info, int index) const;
		void	_print_search_contact(int index) const;
};

#endif