/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:44:09 by kaye              #+#    #+#             */
/*   Updated: 2021/08/20 13:58:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

int main() {
	Data data('*', 42, "42str");

	std::cout << "\e[1;32m- Data -\e[0m" << std::endl;
	std::cout << "char: " << data.getC() << std::endl;
	std::cout << "int: " << data.getI() << std::endl;
	std::cout << "str: " << data.getStr() << std::endl;
	std::cout << std::endl;

	uintptr_t serializeData = serialize(&data);

	std::cout << "\e[1;32m- Serialize -\e[0m" << std::endl;
	std::cout << serializeData << std::endl;
	std::cout << std::endl;

	Data *deserializeData = deserialize(serializeData);
	std::cout << "\e[1;32m- Deserialize -\e[0m" << std::endl;
	std::cout << "char: " << deserializeData->getC() << std::endl;
	std::cout << "int: " << deserializeData->getI() << std::endl;
	std::cout << "str: " << deserializeData->getStr() << std::endl;

	return (0);
}