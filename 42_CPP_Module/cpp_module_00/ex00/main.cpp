/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:49:16 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:51:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

char	*my_strupr(char *s) {
	for (int i = 0; s[i]; i++) {
		s[i] = (char)toupper(s[i]);
	}
	return s;
}

int	main(int ac, char **av) {
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else {
		for (int i = 1; av[i]; i++) {
			std::cout << my_strupr(av[i]);
		}
		std::cout << std::endl;
	}
	return 0;
}
