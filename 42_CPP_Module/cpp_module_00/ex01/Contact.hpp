/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:46:00 by kaye              #+#    #+#             */
/*   Updated: 2021/08/18 16:22:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

#define INFO_NBR 5

enum	e_info {
	e_FIRST_NAME,
	e_LAST_NAME,
	e_NICKNAME,
	e_PHONE_NBR,
	e_DARKEST_SECRET
};

class Contact {
	public:
		Contact(void);
		~Contact(void);

	public:
		std::string get_info(int info_i) const;
		void		set_info(std::string to_set, int info_i);
		void		info_clean(void);
		bool		info_is_empty(void) const;

	private:
		std::string	_info[INFO_NBR];
};

#endif
