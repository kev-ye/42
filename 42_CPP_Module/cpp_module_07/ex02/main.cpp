/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 16:17:36 by kaye              #+#    #+#             */
/*   Updated: 2021/08/20 18:43:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

void test1(void) {
	std::cout << "\e[1;32m- Empty array test -\e[0m" << std::endl;
	Array<int> arrayInt;
	std::cout << "\e[1;33mArray:\e[0m <int>" << std::endl;
	std::cout << "\e[1;35mSize:\e[0m " << arrayInt.size() << std::endl;

	try {
		std::cout << "\e[1;34mAssignment:\e[0m arrayInt[0] = 1: ";
		arrayInt[0] = 1;
		std::cout << arrayInt[0] << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
}

void test2(void) {
	std::cout << "\e[1;32m- Basic test -\e[0m" << std::endl;
	Array<int> arrayInt(10);
	std::cout << "\e[1;33mArray:\e[0m <int>" << std::endl;
	std::cout << "\e[1;35mSize:\e[0m " << arrayInt.size() << std::endl;

	std::cout << "\e[1;34mDefault initialized:\e[0m ";
	for (int i = 0; i < 10; i++)
		std::cout << arrayInt[i] << ((i != 9) ? ", " : "\n");

	std::cout << "\e[1;36mAfter assignment of value:\e[0m ";
	for (int i = 0; i < 10; i++)
		arrayInt[i] = i + 1;

	for (int i = 0; i < 10; i++)
		std::cout << arrayInt[i] << ((i != 9) ? ", " : "\n");

	std::cout << std::endl;

	Array<std::string> arrayStr(3);
	std::cout << "\e[1;33mArray:\e[0m <std::string>" << std::endl;
	std::cout << "\e[1;35mSize:\e[0m " << arrayStr.size() << std::endl;

	std::cout << "\e[1;34mDefault initialized:\e[0m ";
	for (int i = 0; i < 3; i++)
		std::cout << arrayStr[i] << ((i != 2) ? ", " : "\n");

	std::cout << "\e[1;36mAfter assignment of value:\e[0m ";
	arrayStr[0] = std::string("Hello");
	arrayStr[1] = std::string("world");
	arrayStr[2] = std::string("!");

	for (int i = 0; i < 3; i++)
		std::cout << arrayStr[i] << ((i != 2) ? ", " : "\n");

	std::cout << std::endl;
}

void test3(void) {
	std::cout << "\e[1;32m- Deep copy test -\e[0m" << std::endl;
	Array<int> arrayInt1(10);
	std::cout << "\e[1;33mArray:\e[0m 1: <int>" << std::endl;
	std::cout << "\e[1;35mSize:\e[0m 1: " << arrayInt1.size() << std::endl;

	std::cout << "\e[1;34mDefault initialized:\e[0m 1: ";
	for (int i = 0; i < 10; i++)
		std::cout << arrayInt1[i] << ((i != 9) ? ", " : "\n");

	std::cout << "\e[1;36mAfter assignment of value:\e[0m 1: ";
	for (int i = 0; i < 10; i++)
		arrayInt1[i] = i + 1;

	for (int i = 0; i < 10; i++)
		std::cout << arrayInt1[i] << ((i != 9) ? ", " : "\n");

	std::cout << std::endl;

	std::cout << "arrayInt1 = arrayInt2" << std::endl;
	std::cout << std::endl;

	Array<int> arrayInt2(10);
	arrayInt2 = arrayInt1;
	std::cout << "\e[1;33mArray:\e[0m 2: <int>" << std::endl;
	std::cout << "\e[1;35mSize:\e[0m 2: " << arrayInt2.size() << std::endl;

	std::cout << "\e[1;34mDefault initialized:\e[0m 2: ";
	for (int i = 0; i < 10; i++)
		std::cout << arrayInt2[i] << ((i != 9) ? ", " : "\n");

	for (int i = 0; i < 10; i++)
		arrayInt2[i] = i + 11;
	std::cout << "\e[1;36mAfter assignment of value:\e[0m\n";

	std::cout << "1: ";
	for (int i = 0; i < 10; i++)
		std::cout << arrayInt1[i] << ((i != 9) ? ", " : "\n");

	std::cout << "2: ";
	for (int i = 0; i < 10; i++)
		std::cout << arrayInt2[i] << ((i != 9) ? ", " : "\n");

	std::cout << std::endl;
}

void test4(void) {
	std::cout << "\e[1;32m- Out of the limits test -\e[0m" << std::endl;
	Array<int> arrayInt(1);
	std::cout << "\e[1;33mArray:\e[0m <int>" << std::endl;
	std::cout << "\e[1;35mSize:\e[0m " << arrayInt.size() << std::endl;

	std::cout << "\e[1;34mDefault initialized:\e[0m ";
	std::cout << arrayInt[0] << std::endl;

	std::cout << "\e[1;34mAssignment:\e[0m arrayInt[0] = 1: ";
	arrayInt[0] = 1;
	std::cout << arrayInt[0] << std::endl;

	try {
		std::cout << "\e[1;34mAssignment:\e[0m arrayInt[1] = 2: ";
		arrayInt[1] = 1;
		std::cout << arrayInt[1] << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

int main(void) {
	test1();
	test2();
	test3();
	test4();

	return 0;
}

// #include <iostream>
// #include <cstdlib>
// #include "Array.hpp"

// #define MAX_VAL 750
// int main(int, char**)
// {
//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     // SCOPE
//     // {
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//     // }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     try
//     {
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     try
//     {
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         numbers[i] = rand();
//     }
//     delete [] mirror;//
//     return 0;
// }