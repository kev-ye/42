/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:53:40 by kaye              #+#    #+#             */
/*   Updated: 2021/10/14 16:28:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Custom.hpp"
#include "set.hpp"
#include <set>
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
void	printSize(__NS__::set<T> s) {
	std::cout << "size: " << s.size() << std::endl;
	std::cout << "maxSize: " << s.max_size() << std::endl;
	std::cout << std::endl;
}

template < class T, class Compare >
void	printSize(__NS__::set<T, Compare> s) {
	std::cout << "size: " << s.size() << std::endl;
	std::cout << "maxSize: " << s.max_size() << std::endl;
	std::cout << std::endl;
}

bool	fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp { bool operator() (const int& lhs, const int& rhs) const { return lhs < rhs; } };

/**
 * @brief constructor test
 */

void	constructTest(void) {
	printTitle("Constructor");

	std::cout << "empty construct:\n";
	__NS__::set<int> s1;
	printSize(s1);
	
    int i[] = {10, 20, 30, 40, 50};
	std::cout << "range: i -> i + 5:\n";
	__NS__::set<int> s2(i, i + 5);
	printSize(s2);
	
	std::cout << "copy: s3(s2):\n";
	__NS__::set<int> s3(s2);
	printSize(s3);

	std::cout << "range with iterator\n";
	__NS__::set<int> s4(s2.begin(), s2.end());
	printSize(s4);

	std::cout << "class as Compare\n";
	__NS__::set<int, classcomp> s5; 
	printSize(s5);

	std::cout << "function pointer as Compare\n";
	bool (*fn_pt)(int, int) = fncomp;
	__NS__::set<int, bool (*)(int, int)> s6(fn_pt);
	printSize(s6);

	std::cout << "s1 = s2\n";
	s1 = s2;
	std::cout << "clear s2\n";
	s2.clear();

	std::cout << "s1:\n";
	printSize(s1);
	std::cout << "s2:\n";
	printSize(s2);
}

/**
 * @brief iterator test
*/

void	iteratorTest(void) {
	printTitle("Iterator");

	int i[] = {10, 20, 30, 40, 50};
	std::cout << "range: i -> i + 5:\n";
	__NS__::set<int> s1(i, i + 5);
	printSize(s1);

	__NS__::set<int>::iterator it = s1.begin();
	std::cout << "begin -> end:\n";
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	it = s1.begin();

	__NS__::set<int>::const_iterator cit = it;

	std::cout << "cmp it == const it: ";
	if (cit == it)
		std::cout << "Yes" << std::endl;
	else
		std::cout << "No" << std::endl;

	std::cout << "rbegin -> rend:\n";
	__NS__::set<int>::reverse_iterator rit = s1.rbegin();
	__NS__::set<int>::reverse_iterator rite = s1.rend();
	for (; rit != rite; rit++)
		std::cout << *rit << std::endl;
	std::cout << std::endl;
}

/**
 * @brief empty test
*/

void	emptyTest(void) {
	printTitle("Empty");

	std::cout << "set<int>\n";
	__NS__::set<int> s1;
	std::cout << (s1.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	printSize(s1);

	std::cout << "set<int> + 1: ";
	s1.insert(1);
	std::cout << (s1.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	printSize(s1);

	std::cout << "set<Custom>\n";
	__NS__::set<Custom> s2;
	std::cout << (s2.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	printSize(s2);

	std::cout << "set<Custom> + 1: ";
	s2.insert(Custom(1, "custom"));
	std::cout << (s2.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	printSize(s2);
}

/**
 * @brief size/max_size test
*/

void	sizeTest(void) {
	printTitle("Size/Max_size");

	std::cout << "set<int>\n";
	__NS__::set<int> s1;
	printSize(s1);

	std::cout << "set<char>\n";
	__NS__::set<char> s2;
	printSize(s2);

	std::cout << "set<short>\n";
	__NS__::set<short> s3;
	printSize(s3);

	std::cout << "set<long long>\n";
	__NS__::set<long long> s4;
	printSize(s4);

	std::cout << "set<double>\n";
	__NS__::set<double> s5;
	printSize(s5);

	std::cout << "set<float>\n";
	__NS__::set<float> s6;
	printSize(s6);

	std::cout << "set<Custom>\n";
	__NS__::set<Custom> s7;
	printSize(s7);
}

/**
 * @brief insert test
*/

void	insertTest(void) {
	printTitle("insert");

	std::cout << "set<int>\n";
	__NS__::set<int> s1;
	printSize(s1);

	std::cout << "insert 100\n";
	s1.insert(100);
	printSize(s1);
	std::cout << "insert 200\n";
	s1.insert(200);
	printSize(s1);
	std::cout << "insert 300\n";
	s1.insert(300);
	printSize(s1);
	std::cout << "insert 400\n";
	s1.insert(400);
	printSize(s1);

	std::cout << "show content:\n";
	__NS__::set<int>::iterator it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	std::cout << "set<Custom>\n";
	__NS__::set<Custom> s2;
	printSize(s2);

	std::cout << "insert Custom(1, \"c\")\n";
	s2.insert(Custom(1, "c"));
	printSize(s2);
	std::cout << "insert Custom(2, \"u\")\n";
	s2.insert(Custom(2, "u"));
	printSize(s2);
	std::cout << "insert Custom(3, \"s\")\n";
	s2.insert(Custom(3, "s"));
	printSize(s2);
	std::cout << "insert Custom(4, \"t\")\n";
	s2.insert(Custom(4, "t"));
	printSize(s2);
	std::cout << "insert Custom(5, \"o\")\n";
	s2.insert(Custom(5, "o"));
	printSize(s2);
	std::cout << "insert Custom(6, \"m\")\n";
	s2.insert(Custom(6, "m"));
	printSize(s2);

	std::cout << "show content:\n";
	__NS__::set<Custom>::iterator it2 = s2.begin();
	for (; it2 != s2.end(); it2++)
		std::cout << it2->getStr() << std::endl;
	std::cout << std::endl;

	std::cout << "insert Custom(1, 'c') again (single insert):\n";
	__NS__::pair<__NS__::set<Custom>::iterator, bool> get = s2.insert(Custom(1, "c"));
	std::cout << std::boolalpha;
	std::cout << "iterator ret: \'" << get.first->getStr() << "\' and bool ret: " << get.second << std::endl;
	printSize(s2);
	
	std::cout << "insert Custom(7, \"something\") (hint insert):\n";
	__NS__::set<Custom>::iterator itc = s2.begin();
	itc++;
	itc++;

	s2.insert(itc, Custom(7, "something"));
	std::cout << "show content:\n";
	it2 = s2.begin();
	for (; it2 != s2.end(); it2++)
		std::cout << it2->getStr() << std::endl;
	std::cout << std::endl;
	
	std::cout << "insert content of s2 (2u 3s 4t 5o) -> s3 (range):\n";
	__NS__::set<Custom> s3;
	printSize(s3);
	itc = s2.begin();
	__NS__::set<Custom>::iterator itc2 = s2.end();

	itc++;
	itc2--;
	itc2--;
	s3.insert(itc, itc2);

	std::cout << "show content:\n";
	itc = s3.begin();
	for (; itc != s3.end(); itc++)
		std::cout << itc->getStr() << std::endl;
	std::cout << std::endl;
}


/**
 * @brief erase test
*/

void	eraseTest(void) {
	printTitle("erase");

	std::cout << "set<int>\n";
	__NS__::set<int> s1;

	std::cout << "+ 100\n";
	s1.insert(100);
	std::cout << "+ 200\n";
	s1.insert(200);
	std::cout << "+ 300\n";
	s1.insert(300);
	std::cout << "+ 400\n";
	s1.insert(400);
	printSize(s1);

	std::cout << "show content:\n";
	__NS__::set<int>::iterator it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	std::cout << "erase by val: \'200\'\n";
	s1.erase(200);
	printSize(s1);

	std::cout << "show content:\n";
	it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	std::cout << "erase by position: \'begin\'\n";
	s1.erase(s1.begin());
	printSize(s1);

	std::cout << "show content:\n";
	it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	
	std::cout << "erase by range: begin -> end\n";
	s1.erase(s1.begin(), s1.end());
	std::cout << "show content:\n";
	if (s1.empty() == true)
		std::cout << "s1 is empty" << std::endl;
	else {
		it = s1.begin();
		for (; it != s1.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}
}

/**
 * @brief swap test
*/

void	swapTest(void) {
	printTitle("swap");

	std::cout << "set<int>\n";
	__NS__::set<int> s1;
	__NS__::set<int> s2;
	
	std::cout << "s1 + 100\n";
	s1.insert(100);
	std::cout << "s1 + 200\n";
	s1.insert(200);
	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "s2 + 11\n";
	s2.insert(11);
	std::cout << "s2 + 22\n";
	s2.insert(22);
	std::cout << "s2 + 33\n";
	s2.insert(33);
	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s2.begin(); it != s2.end(); ++it)
		std::cout << *it << '\n';
	printSize(s2);

	std::cout << "swap s1 and s2\n";
	s1.swap(s2);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s2.begin(); it != s2.end(); ++it)
		std::cout << *it << '\n';
	printSize(s2);
}

/**
 * @brief clear test
*/

void	clearTest(void) {
	printTitle("clear");

	__NS__::set<int> s1;

	std::cout << "+ 100\n";
	s1.insert(100);
	std::cout << "+ 200\n";
	s1.insert(200);
	std::cout << "+ 300\n";
	s1.insert(300);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "s1 clear:\n";
	s1.clear();
	std::cout << "show content:\n";
	if (s1.empty() == true)
		std::cout << "s1 is empty\n";
	else {
		for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	}
	printSize(s1);

	std::cout << "+ 1101\n";
	s1.insert(1101);
	std::cout << "+ 2202\n";
	s1.insert(2202);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);
}

/**
 * @brief keyComp test
*/

void	keyCompTest(void) {
	printTitle("keyComp");

	__NS__::set<int> s1;
	__NS__::set<int>::key_compare s1Comp = s1.key_comp();

	std::cout << "+ 0 -> 5\n";
	for (int i = 0; i <= 5; i++)
		s1.insert(i);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	int highest = *s1.rbegin();

	std::cout << "show content with comp:\n";
	__NS__::set<int>::iterator it = s1.begin();
	do {
		std::cout << *it << '\n';
	} while (s1Comp(*(++it), highest));

	std::cout << std::endl;
}

/**
 * @brief valueComp test
*/

void	valueCompTest(void) {
	printTitle("valueComp");

	__NS__::set<int> s1;
	__NS__::set<int>::key_compare s1Comp = s1.value_comp();

	std::cout << "+ 0 -> 5\n";
	for (int i = 0; i <= 5; i++)
		s1.insert(i);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	int highest = *s1.rbegin();

	std::cout << "show content with comp:\n";
	__NS__::set<int>::iterator it = s1.begin();
	do {
		std::cout << *it << '\n';
	} while (s1Comp(*(++it), highest));

	std::cout << std::endl;
}

/**
 * @brief find test
*/

void	findTest(void) {
	printTitle("find");
	
	__NS__::set<int> s1;
	__NS__::set<int>::iterator it;

	std::cout << "+ 10 -> 50\n";
	for (int i = 1; i <= 5; i++)
		s1.insert(i * 10);

	std::cout << "show content:\n";
	for (it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "find \'20\' and erase it\n";
	it = s1.find(20);
	if (it != s1.end())
		s1.erase (it);
	
	std::cout << "show content:\n";
	for (it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "find element and print it:\n";
	std::cout << "find 10 => " << *s1.find(10) << '\n';
	std::cout << "find 30 => " << *s1.find(30) << '\n';
	std::cout << "find 40 => " << *s1.find(40)<< '\n';
	std::cout << "find 50 => " << *s1.find(50)<< '\n';
}

/**
 * @brief count test
*/

void	countTest(void) {
	printTitle("count");

	__NS__::set<int> s1;

	std::cout << "+ 3 6 9 12\n";
	for (int i = 1; i < 5; i++)
		s1.insert(i * 3);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "check element with a loop a -> h:\n";
	for (int i = 0; i <= 12; i++) {
		std::cout << i;
		if (s1.count(i) != 0)
			std::cout << " is an element of s1.\n";
		else 
			std::cout << " is not an element of s1.\n";
	}
}

/**
 * @brief bound test
*/

void	boundTest(void) {
	printTitle("lowerBound/upperBound");

	__NS__::set<int> s1;
	__NS__::set<int>::iterator itlow;
	__NS__::set<int>::iterator itup;

	std::cout << "+ 10 -> 100\n";
	for (int i = 1; i <= 10; i++)
		s1.insert(i * 10);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "set lower_bound(\'30\') and upper_bound(\'60\')\n";
	itlow = s1.lower_bound (30);
	itup = s1.upper_bound (60);

	std::cout << "erase range of itlow -> itup\n";
	s1.erase(itlow, itup);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);
}

/**
 * @brief equalRange test
*/

void	equalRangeTest(void) {
	printTitle("equalRange");

	__NS__::set<int> s1;

	std::cout << "+ 10 -> 100\n";
	for (int i = 1; i <= 10; i++)
		s1.insert(i * 10);

	std::cout << "show content:\n";
	for (__NS__::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	printSize(s1);

	std::cout << "set equal_range(\'30\')\n";
	__NS__::pair<__NS__::set<int>::iterator, __NS__::set<int>::iterator> ret;
	ret = s1.equal_range(30);

	std::cout << "lower bound points to: ";
	std::cout << *ret.first << '\n';

	std::cout << "upper bound points to: ";
	std::cout << *ret.second << '\n';
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
			<< "- \033[1;36memptyTest\033[0m: launch about empty test\n"
			<< "- \033[1;36msizeTest\033[0m: launch about size/max_size/capacity test\n"
			<< "- \033[1;36minsertTest\033[0m: launch about insert test\n"
			<< "- \033[1;36meraseTest\033[0m: launch about erase test\n"
			<< "- \033[1;36mswaptTest\033[0m: launch about swap test\n"
			<< "- \033[1;36mclearTest\033[0m: launch about clear test\n"
			<< "- \033[1;36mkeyCompTest\033[0m: launch about keyComp test\n"
			<< "- \033[1;36mvalueCompTest\033[0m: launch about valueComp test\n"
			<< "- \033[1;36mfindTest\033[0m: launch about find test\n"
			<< "- \033[1;36mcountTest\033[0m: launch about count test\n"
			<< "- \033[1;36mboundTest\033[0m: launch about bound test\n"
			<< "- \033[1;36mequalRangeTest\033[0m: launch about equalRange test\n";
		return 0;
	}

	Test test[] = {
		{"constructTest", &constructTest},
		{"iteratorTest", &iteratorTest},
		{"emptyTest", &emptyTest},
		{"sizeTest", &sizeTest},
		{"insertTest", &insertTest},
		{"eraseTest", &eraseTest},
		{"swapTest", &swapTest},
		{"clearTest", &clearTest},
		{"keyCompTest", &keyCompTest},
		{"valueCompTest", &valueCompTest},
		{"findTest", &findTest},
		{"countTest", &countTest},
		{"boundTest", &boundTest},
		{"equalRangeTest", &equalRangeTest}};

	if (std::string(av[1]) == "all") {
		for (int i = 0; i < 14; i++)
			test[i].fptr();
		return 0;
	}

	std::string arg(av[1]);
	for (int i = 0; i < 14; i++) {
		if (test[i].testName == arg) {
			test[i].fptr();
			return 0;
		}
	}
	return 1;
}