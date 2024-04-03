/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:26:05 by kaye              #+#    #+#             */
/*   Updated: 2021/07/28 14:39:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int main(int ac, char **av) {

	if (ac != 2) {

		std::cout << "usage: ./karenFilter [log_level]" << std::endl;
		return (1);
	}
	
	Karen karen_filter;

	karen_filter.complain(av[1]);
	return (0);
}