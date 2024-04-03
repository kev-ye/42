/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:37:27 by kaye              #+#    #+#             */
/*   Updated: 2021/10/14 16:28:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Custom.hpp"
#include "map.hpp"
#include <map>
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

template < class Key, class T >
void	printSize(__NS__::map<Key, T> m) {
	std::cout << "size: " << m.size() << std::endl;
	std::cout << "maxSize: " << m.max_size() << std::endl;
	std::cout << std::endl;
}

template < class Key, class T, class Compare >
void	printSize(__NS__::map<Key, T, Compare> m) {
	std::cout << "size: " << m.size() << std::endl;
	std::cout << "maxSize: " << m.max_size() << std::endl;
	std::cout << std::endl;
}

bool	fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp { bool operator() (const char& lhs, const char& rhs) const { return lhs < rhs; } };

/**
 * @brief constructor test
 */

void	constructTest(void) {
	printTitle("Constructor");

	std::cout << "basic construct: + (a, 10) (b, 20) (c, 30) (d, 40):\n";
	__NS__::map<char, int> m1;
	m1['a'] = 10;
	m1['b'] = 20;
	m1['c'] = 30;
	m1['d'] = 40;
	printSize(m1);
	
	std::cout << "range: m1.begin -> m1.end:\n";
	__NS__::map<char, int> m2(m1.begin(), m1.end());
	printSize(m2);
	
	std::cout << "copy: m3(m2):\n";
	__NS__::map<char, int> m3(m2);
	printSize(m3);

	std::cout << "class as Compare\n";
	__NS__::map<char, int, classcomp> m4; 
	printSize(m4);

	std::cout << "function pointer as Compare\n";
	bool (*fn_pt)(char, char) = fncomp;
	__NS__::map<char, int, bool (*)(char,char)> m5(fn_pt);
	printSize(m4);

	std::cout << "basic assign: m6: + (a, 100):\n";
	__NS__::map<char, int> m6;
	m6['a'] = 100;
	printSize(m6);

	std::cout << "m6 = m1\n";
	m6 = m1;
	std::cout << "clear m1\n";
	m1.clear();

	std::cout << "m1:\n";
	printSize(m1);
	std::cout << "m6:\n";
	printSize(m6);
}

/**
 * @brief iterator test
*/

void	iteratorTest(void) {
	printTitle("Iterator");

	std::cout << "basic construct: + (a, 10) (b, 20) (c, 30) (d, 40):\n";
	__NS__::map<char, int> m1;
	m1['a'] = 10;
	m1['b'] = 20;
	m1['c'] = 30;
	m1['d'] = 40;
	printSize(m1);

	__NS__::map<char, int>::iterator it = m1.begin();
	std::cout << "begin -> end:\n";
	for (; it != m1.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	std::cout << std::endl;

	it = m1.begin();

	__NS__::map<char, int>::const_iterator cit = it;

	std::cout << "cmp it == const it: ";
	if (cit == it)
		std::cout << "Yes" << std::endl;
	else
		std::cout << "No" << std::endl;

	std::cout << "rbegin -> rend:\n";
	__NS__::map<char, int>::reverse_iterator rit = m1.rbegin();
	__NS__::map<char, int>::reverse_iterator rite = m1.rend();
	for (; rit != rite; rit++)
		std::cout << rit->first << ": " << rit->second << std::endl;
	std::cout << std::endl;
}

/**
 * @brief empty test
*/

void	emptyTest(void) {
	printTitle("Empty");

	std::cout << "map<char, int>\n";
	__NS__::map<char, int> m1;
	std::cout << (m1.empty() == true ? "m1 is empty" : "m1 is not empty") << std::endl;
	printSize(m1);

	std::cout << "map<char, int> + 1: ";
	m1['a'] = 100;
	std::cout << (m1.empty() == true ? "m1 is empty" : "m1 is not empty") << std::endl;
	printSize(m1);

	std::cout << "map<char, Custom>\n";
	__NS__::map<char, Custom> m2;
	std::cout << (m2.empty() == true ? "m1 is empty" : "m1 is not empty") << std::endl;
	printSize(m2);

	std::cout << "map<char, Custom> + 1: ";
	m2['a'] = Custom(1, "custom");
	std::cout << (m2.empty() == true ? "m1 is empty" : "m1 is not empty") << std::endl;
	printSize(m2);
}

/**
 * @brief size/max_size test
*/

void	sizeTest(void) {
	printTitle("Size/Max_size");

	std::cout << "map<int, int>\n";
	__NS__::map<int, int> m1;
	printSize(m1);

	std::cout << "map<char, int>\n";
	__NS__::map<char, int> m2;
	printSize(m2);

	std::cout << "map<char, char>\n";
	__NS__::map<char, char> m3;
	printSize(m3);

	std::cout << "map<long, long long>\n";
	__NS__::map<long, long long> m4;
	printSize(m4);

	std::cout << "map<double, float>\n";
	__NS__::map<double, float> m5;
	printSize(m5);

	std::cout << "map<Custom, Custom>\n";
	__NS__::map<Custom, Custom> m6;
	printSize(m6);
}

/**
 * @brief element access test
*/

void	elementAccessTest(void) {
	printTitle("Element access");
	
	std::cout << "map<char, int>\n";
	__NS__::map<char, int> m1;
	printSize(m1);

	std::cout << "Insert with operator[]:\n";
	std::cout << "+ a 100\n";
	m1['a'] = 100;
	printSize(m1);
	std::cout << "+ b 200\n";
	m1['b'] = 200;
	printSize(m1);
	std::cout << "+ c 300\n";
	m1['c'] = 300;
	printSize(m1);
	std::cout << "+ d 400\n";
	m1['d'] = 400;
	printSize(m1);

	std::cout << "show content:\n";
	__NS__::map<char, int>::iterator it = m1.begin();
	for (; it != m1.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "map<char, Custom>\n";
	__NS__::map<char, Custom> m2;
	printSize(m2);

	std::cout << "+ a Custom(1, 'c')\n";
	m2['a'] = Custom(1, "c");
	printSize(m2);
	std::cout << "+ b Custom(2, 'u')\n";
	m2['b'] = Custom(2, "u");
	printSize(m2);
	std::cout << "+ c Custom(3, 's')\n";
	m2['c'] = Custom(3, "s");
	printSize(m2);
	std::cout << "+ d Custom(4, 't')\n";
	m2['d'] = Custom(4, "t");
	printSize(m2);
	std::cout << "+ e Custom(5, 'o')\n";
	m2['e'] = Custom(5, "o");
	printSize(m2);
	std::cout << "+ f Custom(6, 'm')\n";
	m2['f'] = Custom(6, "m");
	printSize(m2);

	std::cout << "show content:\n";
	__NS__::map<char, Custom>::iterator it2 = m2.begin();
	for (; it2 != m2.end(); it2++)
		std::cout << it2->first << ": " << it2->second.getStr() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief insert test
*/

void	insertTest(void) {
	printTitle("insert");

	std::cout << "map<char, int>\n";
	__NS__::map<char, int> m1;
	printSize(m1);

	std::cout << "insert a 100\n";
	m1.insert(__NS__::make_pair('a', 100));
	printSize(m1);
	std::cout << "insert b 200\n";
	m1.insert(__NS__::make_pair('b', 200));
	printSize(m1);
	std::cout << "insert c 300\n";
	m1.insert(__NS__::make_pair('c', 300));
	printSize(m1);
	std::cout << "insert d 400\n";
	m1.insert(__NS__::make_pair('d', 400));
	printSize(m1);

	std::cout << "show content:\n";
	__NS__::map<char, int>::iterator it = m1.begin();
	for (; it != m1.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "map<char, Custom>\n";
	__NS__::map<char, Custom> m2;
	printSize(m2);

	std::cout << "insert a Custom(1, \"c\")\n";
	m2.insert(__NS__::make_pair('a', Custom(1, "c")));
	printSize(m2);
	std::cout << "insert b Custom(2, \"u\")\n";
	m2.insert(__NS__::make_pair('b', Custom(2, "u")));
	printSize(m2);
	std::cout << "insert c Custom(3, \"s\")\n";
	m2.insert(__NS__::make_pair('c', Custom(3, "s")));
	printSize(m2);
	std::cout << "insert d Custom(4, \"t\")\n";
	m2.insert(__NS__::make_pair('d', Custom(4, "t")));
	printSize(m2);
	std::cout << "insert e Custom(5, \"o\")\n";
	m2.insert(__NS__::make_pair('e', Custom(5, "o")));
	printSize(m2);
	std::cout << "insert f Custom(6, \"m\")\n";
	m2.insert(__NS__::make_pair('f', Custom(6, "m")));
	printSize(m2);

	std::cout << "show content:\n";
	__NS__::map<char, Custom>::iterator it2 = m2.begin();
	for (; it2 != m2.end(); it2++)
		std::cout << it2->first << ": " << it2->second.getStr() << std::endl;
	std::cout << std::endl;

	std::cout << "insert a Custom(1, 'c') again (single insert):\n";
	__NS__::pair<__NS__::map<char, Custom>::iterator, bool> get = m2.insert(__NS__::make_pair('a', Custom(1, "c")));
	std::cout << std::boolalpha;
	std::cout << "iterator ret: \'" << get.first->first << "\' -> \'" << get.first->second.getStr() << "\' and bool ret: " << get.second << std::endl;
	printSize(m2);
	
	std::cout << "insert g Custom(7, \"something\") (hint insert):\n";
	__NS__::map<char, Custom>::iterator itc = m2.begin();
	itc++;
	itc++;

	m2.insert(itc, __NS__::make_pair('g', Custom(7, "something")));
	std::cout << "show content:\n";
	it2 = m2.begin();
	for (; it2 != m2.end(); it2++)
		std::cout << it2->first << ": " << it2->second.getStr() << std::endl;
	std::cout << std::endl;
	
	std::cout << "insert content of m2 (2u 3s 4t 5o) -> m3 (range):\n";
	__NS__::map<char, Custom> m3;
	printSize(m3);
	itc = m2.begin();
	__NS__::map<char, Custom>::iterator itc2 = m2.end();

	itc++;
	itc2--;
	itc2--;
	m3.insert(itc, itc2);

	std::cout << "show content:\n";
	itc = m3.begin();
	for (; itc != m3.end(); itc++)
		std::cout << itc->first << ": " << itc->second.getStr() << std::endl;
	std::cout << std::endl;
}


/**
 * @brief erase test
*/

void	eraseTest(void) {
	printTitle("erase");

	std::cout << "map<char, int>\n";
	__NS__::map<char, int> m1;

	std::cout << "+ a 100\n";
	m1['a'] = 100;
	std::cout << "+ b 200\n";
	m1['b'] = 200;
	std::cout << "+ c 300\n";
	m1['c'] = 300;
	std::cout << "+ d 400\n";
	m1['d'] = 400;
	printSize(m1);

	std::cout << "show content:\n";
	__NS__::map<char, int>::iterator it = m1.begin();
	for (; it != m1.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "erase by key: \'b\'\n";
	m1.erase('b');
	printSize(m1);

	std::cout << "show content:\n";
	it = m1.begin();
	for (; it != m1.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "erase by position: \'begin\'\n";
	m1.erase(m1.begin());
	printSize(m1);

	std::cout << "show content:\n";
	it = m1.begin();
	for (; it != m1.end(); it++)
		std::cout << it->first << ": " << it->second << std::endl;
	std::cout << std::endl;
	
	std::cout << "erase by range: begin -> end\n";
	m1.erase(m1.begin(), m1.end());
	std::cout << "show content:\n";
	if (m1.empty() == true)
		std::cout << "m1 is empty" << std::endl;
	else {
		it = m1.begin();
		for (; it != m1.end(); it++)
			std::cout << it->first << ": " << it->second << std::endl;
		std::cout << std::endl;
	}
}

/**
 * @brief swap test
*/

void	swapTest(void) {
	printTitle("swap");

	std::cout << "map<char, int>\n";
	__NS__::map<char, int> m1;
	__NS__::map<char, int> m2;
	
	std::cout << "m1 + x 100\n";
	m1['x'] = 100;
	std::cout << "m1 + y 200\n";
	m1['y'] = 200;
	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "m2 + a 11\n";
	m2['a'] = 11;
	std::cout << "m2 + b 22\n";
	m2['b'] = 22;
	std::cout << "m2 + c 33\n";
	m2['c'] = 33;
	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m2.begin(); it != m2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m2);

	std::cout << "swap m1 and m2\n";
	m1.swap(m2);

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m2.begin(); it != m2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m2);
}

/**
 * @brief clear test
*/

void	clearTest(void) {
	printTitle("clear");

	__NS__::map<char, int> m1;

	std::cout << "+ x 100\n";
	m1['x'] = 100;
	std::cout << "+ y 200\n";
	m1['y'] = 200;
	std::cout << "+ z 300\n";
	m1['z'] = 300;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "m1 clear:\n";
	m1.clear();
	std::cout << "show content:\n";
	if (m1.empty() == true)
		std::cout << "m1 is empty\n";
	else {
		for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	}
	printSize(m1);

	std::cout << "+ a 1101\n";
	m1['a'] = 1101;
	std::cout << "+ b 2202\n";
	m1['b'] = 2202;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);
}

/**
 * @brief keyComp test
*/

void	keyCompTest(void) {
	printTitle("keyComp");

	__NS__::map<char, int> m1;
	__NS__::map<char, int>::key_compare m1Comp = m1.key_comp();

	std::cout << "+ a 100\n";
	m1['a'] = 100;
	std::cout << "+ b 200\n";
	m1['b'] = 200;
	std::cout << "+ c 300\n";
	m1['c'] = 300;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	char highest = m1.rbegin()->first;

	std::cout << "show content with comp:\n";
	__NS__::map<char, int>::iterator it = m1.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while (m1Comp((*it++).first, highest));

	std::cout << std::endl;
}

/**
 * @brief valueComp test
*/

void	valueCompTest(void) {
	printTitle("valueComp");

	__NS__::map<char, int> m1;

	std::cout << "+ x 1001\n";
	m1['x'] = 1001;
	std::cout << "+ y 2002\n";
	m1['y'] = 2002;
	std::cout << "+ z 3003\n";
	m1['z'] = 3003;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	__NS__::pair<char, int> highest = *m1.rbegin();

	std::cout << "show content with comp:\n";
	__NS__::map<char, int>::iterator it = m1.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while (m1.value_comp()(*it++, highest));

	std::cout << std::endl;
}

/**
 * @brief find test
*/

void	findTest(void) {
	printTitle("find");
	
	__NS__::map<char, int> m1;
	__NS__::map<char, int>::iterator it;

	std::cout << "+ a 50\n";
	m1['a'] = 50;
	std::cout << "+ b 100\n";
	m1['b'] = 100;
	std::cout << "+ c 150\n";
	m1['c'] = 150;
	std::cout << "+ d 200\n";
	m1['d'] = 200;

	std::cout << "show content:\n";
	for (it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "find \'b\' and erase it\n";
	it = m1.find('b');
	if (it != m1.end())
		m1.erase (it);
	
	std::cout << "show content:\n";
	for (it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "find element and print it:\n";
	std::cout << "find a => " << m1.find('a')->second << '\n';
	std::cout << "find c => " << m1.find('c')->second << '\n';
	std::cout << "find d => " << m1.find('d')->second << '\n';
}

/**
 * @brief count test
*/

void	countTest(void) {
	printTitle("count");

	__NS__::map<char, int> m1;
	char c;

	std::cout << "+ a 101\n";
	m1['a'] = 101;
	std::cout << "+ c 202\n";
	m1['c'] = 202;
	std::cout << "+ f 303\n";
	m1['f'] = 303;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "check element with a loop a -> h:\n";
	for (c = 'a'; c < 'h'; c++) {
		std::cout << c;
		if (m1.count(c) > 0)
			std::cout << " is an element of m1.\n";
		else 
			std::cout << " is not an element of m1.\n";
	}
}

/**
 * @brief bound test
*/

void	boundTest(void) {
	printTitle("lowerBound/upperBound");

	__NS__::map<char, int> m1;
	__NS__::map<char, int>::iterator itlow;
	__NS__::map<char, int>::iterator itup;

	std::cout << "+ a 20\n";
	m1['a'] = 20;
	std::cout << "+ b 40\n";
	m1['b'] = 40;
	std::cout << "+ c 60\n";
	m1['c'] = 60;
	std::cout << "+ d 80\n";
	m1['d'] = 80;
	std::cout << "+ e 100\n";
	m1['e'] = 100;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "set lower_bound(\'b\') and upper_bound(\'d\')\n";
	itlow = m1.lower_bound ('b');
	itup = m1.upper_bound ('d');

	std::cout << "erase range of itlow -> itup\n";
	m1.erase(itlow, itup);

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);
}

/**
 * @brief equalRange test
*/

void	equalRangeTest(void) {
	printTitle("equalRange");

	__NS__::map<char, int> m1;

	std::cout << "+ a 10\n";
	m1['a'] = 10;
	std::cout << "+ b 20\n";
	m1['b'] = 20;
	std::cout << "+ c 30\n";
	m1['c'] = 30;

	std::cout << "show content:\n";
	for (__NS__::map<char, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	printSize(m1);

	std::cout << "set equal_range(\'b\')\n";
	__NS__::pair<__NS__::map<char, int>::iterator, __NS__::map<char, int>::iterator> ret;
	ret = m1.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
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
			<< "- \033[1;36melementAccessTest\033[0m: launch about element access test\n"
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
		{"elementAccessTest", &elementAccessTest},
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
		for (int i = 0; i < 15; i++)
			test[i].fptr();
		return 0;
	}

	std::string arg(av[1]);
	for (int i = 0; i < 15; i++) {
		if (test[i].testName == arg) {
			test[i].fptr();
			return 0;
		}
	}
	return 1;
}