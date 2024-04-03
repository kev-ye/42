/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:56:51 by kaye              #+#    #+#             */
/*   Updated: 2021/08/01 18:29:46 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class Point
{
	public:
		Point(void);
		Point(Fixed const x, Fixed const y);
		Point(Point const & src);
		~Point(void);
	
		Point & operator=(Point const & rhs);

	public:
		Fixed 	getX(void) const;
		Fixed 	getY(void) const;

	private:
		Fixed const _x;
		Fixed const _y;
};

bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
