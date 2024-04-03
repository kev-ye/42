/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:56:28 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:46:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main() {
	std::string string("HI THIS IS BRAIN");
	std::string *stringPTR(&string);
	std::string &stringREF(string);

	std::cout << "string addr    : " << &string << std::endl;
	std::cout << "stringPTR addr : " << stringPTR << std::endl;
	std::cout << "stringREF addr : " << &stringREF << std::endl;
	
	std::cout << std::endl;

	std::cout << "stringPTR content : " << *stringPTR << std::endl;
	std::cout << "stringREF content : " << stringREF << std::endl;

	return (0);
}