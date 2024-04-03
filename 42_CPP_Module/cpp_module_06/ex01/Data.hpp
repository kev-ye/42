/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:01:05 by kaye              #+#    #+#             */
/*   Updated: 2021/08/19 17:18:27 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

#include <iostream>
#include <stdint.h>

class Data {
	public:
		Data(void);
		Data(char const c, int const i, std::string const & str);
		Data(Data const & src);
		virtual ~Data(void);

		Data &	operator=(Data const & rhs);

	public:
		char const &		getC(void) const;
		int const &			getI(void) const;
		std::string const &	getStr(void) const;

	private:
		char		_c;
		int			_i;
		std::string	_str;
};

uintptr_t	serialize(Data *ptr);
Data		*deserialize(uintptr_t raw);

#endif