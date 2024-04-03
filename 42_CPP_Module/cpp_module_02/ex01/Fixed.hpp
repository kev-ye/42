/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 17:34:15 by kaye              #+#    #+#             */
/*   Updated: 2021/08/01 15:02:06 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
	public:
		Fixed(void);
		Fixed(int const	i);
		Fixed(float const f);
		Fixed(Fixed const & src);
		~Fixed(void);
	
		Fixed & operator=(Fixed const & rhs);

	public:
		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		float	toFloat(void) const;
		int		toInt(void) const;

	private:
		int					_fixed;
		static int const	_bits;
};

std::ostream & operator<<(std::ostream & o, Fixed const & i);

#endif