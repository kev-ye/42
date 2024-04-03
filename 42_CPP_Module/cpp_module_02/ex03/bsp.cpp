/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:56:17 by kaye              #+#    #+#             */
/*   Updated: 2021/08/01 17:19:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

float cross_product(Point p1, Point p2, Point p3) {
    return (p2.getX().toFloat() - p1.getX().toFloat()) * (p3.getY().toFloat() - p1.getY().toFloat()) - (p2.getY().toFloat() - p1.getY().toFloat()) * (p3.getX().toFloat() - p1.getX().toFloat());
}

bool	bsp(Point const a, Point const b, Point const c, Point const point) {
	if (cross_product(a, b, c) < 0)
		return bsp(a, c, b, point);
	if (cross_product(a, b, point) > 0 && cross_product(b, c, point) > 0 && cross_product(c, a, point) > 0)
		return (true);
	return (false);
}