/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:38:42 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:55:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KAREN_HPP
# define KAREN_HPP

#include <iostream>

class Karen {
	public:
		Karen(void);
		~Karen(void);

	public:
		void	complain(std::string level);

	private:
		void	_debug(void);
		void	_info(void);
		void	_warning(void);
		void	_error(void);

	private:
		void	(Karen::*_complain[4])(void);
};

enum	e_complain {
	e_DEBUG = 0,
	e_INFO,
	e_WARNING,
	e_ERROR,
	e_COMPLAIN
};
#endif