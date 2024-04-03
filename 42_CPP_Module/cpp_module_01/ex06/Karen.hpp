/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:26:03 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:47:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KAREN_HPP
# define KAREN_HPP

#include <iostream>

enum	e_complain {
	e_DEBUG = 0,
	e_INFO,
	e_WARNING,
	e_ERROR,
	e_COMPLAIN
};

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

#endif