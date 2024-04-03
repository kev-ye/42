/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:37:27 by kaye              #+#    #+#             */
/*   Updated: 2021/10/14 16:28:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Custom.hpp"
#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string>

// #define __NS__ std // default namespace

/**
 * @brief utils
*/

typedef void	(*fp)(void);
struct Test {
	std::string	testName;
	fp const	fptr;
};

void	printTitle(std::string const & title) {
	std::cout << "-- [" << title << "] --" << std::endl;
	std::cout << std::endl;
}

template < class T >
void	printSize(__NS__::vector<T> vec) {
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "maxSize: " << vec.max_size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief constructor test
*/

void	constructTest(void) {
	printTitle("Constructor");

	std::cout << "empty test: int:\n";
	__NS__::vector<int> vecInt;
	printSize(vecInt);

	std::cout << "empty test: Custom Class:\n";
	__NS__::vector<Custom> vecCustom;
	printSize(vecCustom);

	std::cout << "fill test: int:\n";
	__NS__::vector<int> vecInt2(42);
	printSize(vecInt2);

	std::cout << "range test: int:\n";
	__NS__::vector<int> vecInt3(vecInt2.begin(), vecInt2.end());
	printSize(vecInt3);

	std::cout << "range test2: Custom:\n";
	__NS__::vector<Custom> vecCustom2(10);
	__NS__::vector<Custom>::iterator it = vecCustom2.begin();
	__NS__::vector<Custom>::iterator ite = vecCustom2.end();

	it++;
	ite--;
	__NS__::vector<Custom> vecCustom3(it, ite);
	printSize(vecCustom3);

	std::cout << "\ncopy test: Custom:\n";
	__NS__::vector<Custom> vecCustom4(vecCustom3);
	printSize(vecCustom4);

	std::cout << "\noperator= test: Custom:\n";
	vecCustom4 = vecCustom;
	printSize(vecCustom4);
}

/**
 * @brief iterator test
*/

void	iteratorTest(void) {
	printTitle("Iterator");

	__NS__::vector<int> vecInt;
	vecInt.push_back(1);
	vecInt.push_back(2);
	vecInt.push_back(3);
	vecInt.push_back(4);
	vecInt.push_back(5);

	__NS__::vector<int>::iterator it = vecInt.begin();
	__NS__::vector<int>::iterator ite = vecInt.end();
	it++;
	it--;
	it += 1;
	it -= 1;

	it += 1;
	std::cout << "it + 1: " << *it << std::endl;;
	__NS__::vector<int>::const_iterator cit = it - 1;
	std::cout << "it - 1: " << *cit << std::endl;
	
	it[2] = 10;
	std::cout << "it[2] = 10: " << it[2] << std::endl;

	cit = it;
	if (it == cit)
		std::cout << "if it == cit: " << "Yes" << std::endl;
	else
		std::cout << "if it == cit: " << "No" << std::endl;

	for (; it != ite; it++)
		std::cout << "*it: " << *it << std::endl;
	printSize(vecInt);

	__NS__::vector<int>::reverse_iterator rit = vecInt.rbegin();
	__NS__::vector<int>::reverse_iterator rite = vecInt.rend();

	for (; rit != rite; rit++)
		std::cout << "*rit: " << *rit << std::endl;
	printSize(vecInt);
}

/**
 * @brief size/max_size/capacity test
*/

void	sizeTest(void) {
	printTitle("Size/Max_size/Capacity");
	
	__NS__::vector<int> vecInt;
	std::cout << "int: ";
	vecInt.push_back(42);
	printSize(vecInt);

	__NS__::vector<char> vecChar;
	std::cout << "char: ";
	printSize(vecChar);

	__NS__::vector<long> vecLong;
	std::cout << "long: ";
	vecLong.push_back(42);
	printSize(vecLong);

	__NS__::vector<long long> vecLongLong;
	std::cout << "longlong: ";
	printSize(vecLongLong);

	__NS__::vector<Custom> vecCuston;
	std::cout << "custom: ";
	printSize(vecCuston);
}

/**
 * @brief resize test
*/

void	resizeTest(void) {
	printTitle("resize/reserve");

	std::cout << "int: ";
	__NS__::vector<int> vecInt;
	printSize(vecInt);

	std::cout << "add 1: ";
	vecInt.push_back(1);
	printSize(vecInt);

	std::cout << "resize(42): ";
	vecInt.resize(42);
	printSize(vecInt);

	std::cout << "resize(0): ";
	vecInt.resize(0);
	printSize(vecInt);

	std::cout << "reserve(42): ";
	vecInt.reserve(42);
	printSize(vecInt);

	std::cout << "add 0 -> 42: ";
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	printSize(vecInt);

	std::cout << "reserve(0): ";
	vecInt.reserve(0);
	printSize(vecInt);

	std::cout << "Custom: ";
	__NS__::vector<Custom> vecCustom;
	printSize(vecCustom);

	std::cout << "add 1: ";
	vecCustom.push_back(Custom(1, "Custom"));
	printSize(vecCustom);

	std::cout << "resize(42): ";
	vecCustom.resize(42);
	printSize(vecCustom);

	std::cout << "resize(0): ";
	vecCustom.resize(0);
	printSize(vecCustom);

	std::cout << "reserve(42): ";
	vecCustom.reserve(42);
	printSize(vecCustom);

	std::cout << "add 0 -> 42: ";
	for (int i = 0; i <= 42; i++)
		vecCustom.push_back(Custom(i, "Custom"));
	printSize(vecCustom);

	std::cout << "reserve(0): ";
	vecCustom.reserve(0);
	printSize(vecCustom);
}

/**
 * @brief empty test
*/

void	emptyTest(void) {
	printTitle("Empty");

	std::cout << "int: ";
	__NS__::vector<int> vecInt;

	std::cout << "init: ";
	std::cout << (vecInt.empty() == true ? "vecInt is empty" : "vecInt is not empty") << std::endl;

	std::cout << "add 1: ";
	vecInt.push_back(1);

	std::cout << (vecInt.empty() == true ? "vecInt is empty\n" : "vecInt is not empty\n") << std::endl;

	std::cout << "Custom: ";
	__NS__::vector<Custom> vecCustom;

	std::cout << "init: ";
	std::cout << (vecCustom.empty() == true ? "vecCustom is empty" : "vecCustom is not empty") << std::endl;

	std::cout << "add 1: ";
	vecCustom.push_back(Custom(1, "custom"));

	std::cout << (vecCustom.empty() == true ? "vecCustom is empty" : "vecCustom is not empty") << std::endl;
}

/**
 * @brief element access test
*/

void	elementAccessTest(void) {
	printTitle("Element access");

	std::cout << "int: assign 0 -> 42";
	__NS__::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "assign +1 & print with operator[]: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		vecInt[i] += 1;
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	const int i = vecInt[0];
	std::cout << "const int i = vecInt[0]: " << i << std::endl;

	std::cout << "assign +1 & print with at: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		vecInt.at(i) += 1;
		std::cout << vecInt.at(i);
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	const int j = vecInt.at(0);
	std::cout << "const int j = vecInt.at(0): " << j << std::endl;

	std::cout << "first: " <<  *(vecInt.begin()) << " and front: " << vecInt.front() << std::endl;
	std::cout << "last: " <<  *(vecInt.end() - 1) << " and back: " << vecInt.back() << std::endl;

	std::cout << "Custom1: + c u s t o m: ";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(4, "t"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "assign custom -> motsuc with operator[]: ";
	vecCustom[0] = (Custom(1, "m"));
	vecCustom[1] = (Custom(2, "o"));
	vecCustom[2] = (Custom(3, "t"));
	vecCustom[3] = (Custom(4, "s"));
	vecCustom[4] = (Custom(5, "u"));
	vecCustom[5] = (Custom(6, "c"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	const Custom c(vecCustom[0]);
	std::cout << "const Custom c(VecCustom[0]): " << c.getStr() << std::endl;

	std::cout << "assign motsuc -> custom with at: ";
	vecCustom.at(0) = (Custom(1, "c"));
	vecCustom.at(1) = (Custom(2, "u"));
	vecCustom.at(2) = (Custom(3, "s"));
	vecCustom.at(3) = (Custom(4, "t"));
	vecCustom.at(4) = (Custom(5, "o"));
	vecCustom.at(5) = (Custom(6, "m"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	const Custom c2(vecCustom.at(0));
	std::cout << "const Custom c2(vecCustom.at(0)): " << c2.getStr() << std::endl;

	std::cout << "first: " <<  (*(vecCustom.begin())).getStr() << " and front: " << vecCustom.front().getStr() << std::endl;
	std::cout << "last: " <<  (*(vecCustom.end() - 1)).getStr() << " and back: " << vecCustom.back().getStr() << std::endl;
}

/**
 * @brief assign test
*/

void	assignTest(void) {
	printTitle("Assign");

	std::cout << "int: \n";
	__NS__::vector<int> vecInt;

	std::cout << "assigne(42, 1): \n";
	vecInt.assign(42, 1);
	printSize(vecInt);

	std::cout << "custom: \n";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(4, "t"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));
	
	std::cout << "vecCustom: ";
	for (int i = 0; i < vecCustom.back().getI(); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "assign(it, ite): \n";
	__NS__::vector<Custom> vecCustom2;
	__NS__::vector<Custom>::iterator it = vecCustom.begin();
	__NS__::vector<Custom>::iterator ite = vecCustom.end();
	vecCustom2.assign(it, ite);
	std::cout << "vecCustom2: ";
	for (int i = 0; i < vecCustom2.back().getI(); i++)
		std::cout << vecCustom2[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom2);
}

/**
 * @brief push_back/pop_bak test
*/

void	pbTest(void) {
	printTitle("push_back/pop_back");

	std::cout << "int: \n";
	__NS__::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);

	std::cout << "vecInt: (after push_back) + 0 -> 42: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "vecInt: (after pop_back) - 42 -> 0:";
	int size = vecInt.size();
	for (int i = 0; i < size; i++)
		vecInt.pop_back();
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "custom: \n";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(4, "t"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));

	std::cout << "vecCustom: (after push_back) + c u s t o m: ";
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "vecCustom: (after pop_back) - m o t s u c:";
	int s = vecCustom.size();
	for (int i = 0; i < s; i++)
		vecCustom.pop_back();
	std::cout << std::endl;
	printSize(vecCustom);
}

/**
 * @brief insert test
*/

void	insertTest(void) {
	printTitle("insert");

	std::cout << "custom: \n";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));

	std::cout << "vecCustom: + c u s o m: ";
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "insert \'t\' in \'cusom\': single: ";
	__NS__::vector<Custom>::iterator it = vecCustom.begin() + 3;
	vecCustom.insert(it, Custom(4, "t"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "int: \n";
	__NS__::vector<int> vecInt;
	vecInt.push_back(1);
	vecInt.push_back(42);

	std::cout << "VecInt: + 1 42: \n";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "insert 40 * 42 in \'1 42\': fill: ";
	vecInt.insert(vecInt.begin() + 1, 40, 41);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "inset \'1 [41 41 41 ... 41 41 41] 42\' in vecInt2: range:  \n";
	__NS__::vector<int> vecInt2;
	printSize(vecInt2);

	vecInt2.insert(vecInt2.begin(), vecInt.begin() + 1, vecInt.end() - 1);
	for (int i = 0; i < static_cast<int>(vecInt2.size()); i++) {
		std::cout << vecInt2[i];
		if (i < static_cast<int>(vecInt2.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt2);
}

/**
 * @brief erase test
*/

void	eraseTest(void) {
	printTitle("erase");

	std::cout << "int: + 0 -> 42\n";
	__NS__::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	printSize(vecInt);

	std::cout << "erase 1:\n";
	vecInt.erase(vecInt.begin() + 10);
	printSize(vecInt);

	std::cout << "erase range:\n";
	vecInt.erase(vecInt.begin() + 1, vecInt.end() - 1);
	printSize(vecInt);

	std::cout << "Custom: + c u s t o m\n";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(4, "t"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));
	printSize(vecCustom);

	std::cout << "erase 1:\n";
	vecCustom.erase(vecCustom.begin() + 3);
	printSize(vecCustom);

	std::cout << "erase range:\n";
	vecCustom.erase(vecCustom.begin() + 1, vecCustom.end() - 1);
	printSize(vecCustom);
}

/**
 * @brief swap test
*/

void	swapTest(void) {
	printTitle("swap");

	std::cout << "int1: + 0 -> 42: ";
	__NS__::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "int2: + 0 -> 12: ";
	__NS__::vector<int> vecInt2;
	for (int i = 0; i <= 12; i++)
		vecInt2.push_back(i);
	for (int i = 0; i < static_cast<int>(vecInt2.size()); i++) {
		std::cout << vecInt2[i];
		if (i < static_cast<int>(vecInt2.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt2);

	std::cout << "swap int1 <-> int2:\n";
	vecInt.swap(vecInt2);
	std::cout << "int1: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);
	std::cout << "int2: ";
	for (int i = 0; i < static_cast<int>(vecInt2.size()); i++) {
		std::cout << vecInt2[i];
		if (i < static_cast<int>(vecInt2.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt2);

	std::cout << "Custom1: + c u s t o m: ";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(4, "t"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "Custom2: + n o t h i n g: ";
	__NS__::vector<Custom> vecCustom2;
	vecCustom2.push_back(Custom(1, "n"));
	vecCustom2.push_back(Custom(2, "o"));
	vecCustom2.push_back(Custom(3, "t"));
	vecCustom2.push_back(Custom(4, "h"));
	vecCustom2.push_back(Custom(5, "i"));
	vecCustom2.push_back(Custom(6, "n"));
	vecCustom2.push_back(Custom(7, "g"));
	for (int i = 0; i < static_cast<int>(vecCustom2.size()); i++)
		std::cout << vecCustom2[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom2);

	std::cout << "swap Custom1 <-> Custom2:\n";
	vecCustom.swap(vecCustom2);
	std::cout << "Custom1: ";
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);
	std::cout << "Custom2: ";
	for (int i = 0; i < static_cast<int>(vecCustom2.size()); i++)
		std::cout << vecCustom2[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom2);
}

/**
 * @brief clear test
*/

void	clearTest(void) {
	printTitle("clear");

	std::cout << "int: + 0 -> 42: ";
	__NS__::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "clear: \n";
	vecInt.clear();
	printSize(vecInt);

	std::cout << "add + 1 2: ";
	vecInt.push_back(1);
	vecInt.push_back(2);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "Custom1: + c u s t o m: ";
	__NS__::vector<Custom> vecCustom;
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	vecCustom.push_back(Custom(3, "s"));
	vecCustom.push_back(Custom(4, "t"));
	vecCustom.push_back(Custom(5, "o"));
	vecCustom.push_back(Custom(6, "m"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);

	std::cout << "clear: \n";
	vecCustom.clear();
	printSize(vecCustom);

	std::cout << "add + c u: ";
	vecCustom.push_back(Custom(1, "c"));
	vecCustom.push_back(Custom(2, "u"));
	for (int i = 0; i < static_cast<int>(vecCustom.size()); i++)
		std::cout << vecCustom[i].getStr();
	std::cout << std::endl;
	printSize(vecCustom);
}

/**
 * @brief main
*/

int main(int ac, char **av) {
	if (ac == 1) {
		printTitle("Args help");
		
		std::cout << "- \033[1;36mall\033[0m: launch all test\n"
			<< "- \033[1;36mconstructTest\033[0m: launch about constructor test\n"
			<< "- \033[1;36miteratorTest\033[0m: launch about iterator test\n"
			<< "- \033[1;36msizeTest\033[0m: launch about size/max_size/capacity test\n"
			<< "- \033[1;36mresizeTest\033[0m: launch about resize test\n"
			<< "- \033[1;36memptyTest\033[0m: launch about empty test\n"
			<< "- \033[1;36melementAccessTest\033[0m: launch about element access test\n"
			<< "- \033[1;36massignTest\033[0m: launch about assign test\n"
			<< "- \033[1;36mpbTest\033[0m: launch about push_back/pop_back test\n"
			<< "- \033[1;36minsertTest\033[0m: launch about insert test\n"
			<< "- \033[1;36mswaptTest\033[0m: launch about swap test\n"
			<< "- \033[1;36mclearTest\033[0m: launch about clear test\n";
		return 0;
	}

	Test test[] = {
		{"constructTest", &constructTest},
		{"iteratorTest", &iteratorTest},
		{"sizeTest", &sizeTest},
		{"resizeTest", &resizeTest},
		{"emptyTest", &emptyTest},
		{"elementAccessTest", &elementAccessTest},
		{"assignTest", &assignTest},
		{"pbTest", &pbTest},
		{"insertTest", &insertTest},
		{"eraseTest", &eraseTest},
		{"swapTest", &swapTest},
		{"clearTest", &clearTest}};

	if (std::string(av[1]) == "all") {
		for (int i = 0; i < 12; i++)
			test[i].fptr();
		return 0;
	}

	std::string arg(av[1]);
	for (int i = 0; i < 12; i++) {
		if (test[i].testName == arg) {
			test[i].fptr();
			return 0;
		}
	}

	return 1;
}