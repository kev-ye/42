/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:22:08 by kaye              #+#    #+#             */
/*   Updated: 2021/08/22 19:01:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include "easyfind.hpp"

void	print(int i) {
	std::cout << ' ' << i;
}

int main(void) {
	/* test with container vector*/
	std::vector<int> vec(4, 100);
	for (int i = 0; i < 10; i++)
		vec.push_back(i);

	std::cout << "\e[1;32mVec init:\e[0m";
	std::for_each(vec.begin(), vec.end(), print);
	std::cout << "\n" << std::endl;

	tryToFind< std::vector<int> >(vec, 1);
	std::cout << std::endl;

	tryToFind< std::vector<int> >(vec, 10);
	std::cout << std::endl;

	tryToFind< std::vector<int> >(vec, 100);
	std::cout << std::endl;

	/* test with container list*/
	std::list<int> lst(4, 100);
	for (int i = 0; i < 10; i++)
		lst.push_back(i);

	std::cout << "\e[1;32mList init:\e[0m";
	std::for_each(lst.begin(), lst.end(), print);
	std::cout << "\n" << std::endl;

	tryToFind< std::list<int> >(lst, 1);
	std::cout << std::endl;

	tryToFind< std::list<int> >(lst, 10);
	std::cout << std::endl;

	tryToFind< std::list<int> >(lst, 100);
	std::cout << std::endl;

	return 0;
} 