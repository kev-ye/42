/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:37:27 by kaye              #+#    #+#             */
/*   Updated: 2021/10/14 16:28:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Custom.hpp"
#include "stack.hpp"
#include <stack>
#include <vector>
#include <deque>
#include <list>
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

template < class T, class Container >
void	printSize(__NS__::stack<T, Container> stack) {
	std::cout << "size: " << stack.size() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief constructor test
 */

void	constructTest(void) {
	printTitle("Constructor");

	std::cout << "construct empty stk:\n";
	__NS__::stack<int> stk;
	printSize(stk);

	std::cout << "stack initialized to copy of vector(42, 42):\n";
	__NS__::vector<int> vec(42, 42);
	__NS__::stack<int, __NS__::vector<int> > stk2(vec);
	printSize(stk2);

	std::cout << "stack initialized to copy of deque(42, 42):\n";
	std::deque<int> deq(42, 42);
	__NS__::stack<int, std::deque<int> > stk3(deq);
	printSize(stk3);

	std::cout << "stack initialized to copy of list(+ 1 2):\n";
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	__NS__::stack<int, std::list<int> > stk4(lst);
	printSize(stk4);
}

/**
 * @brief empty test
 */

void	emptyTest(void) {
	printTitle("Empty");

	std::cout << "construct empty stk:\n";
	__NS__::stack<int> stk;
	std::cout << (stk.empty() == true ? "stk is empty" : "stk is not empty") << std::endl;
	printSize(stk);

	std::cout << "stack initialized to copy of vector(42, 42):\n";
	__NS__::vector<int> vec(42, 42);
	__NS__::stack<int, __NS__::vector<int> > stk2(vec);
	std::cout << (stk2.empty() == true ? "stk is empty" : "stk is not empty") << std::endl;
	printSize(stk2);
}

/**
 * @brief size test
 */

void	sizeTest(void) {
	printTitle("Size");

	std::cout << "construct empty stk:\n";
	__NS__::stack<int> stk;
	printSize(stk);

	std::cout << "+ 1\n";
	stk.push(1);
	printSize(stk);

	std::cout << "+ 2\n";
	stk.push(2);
	printSize(stk);
}

/**
 * @brief top test
 */

void	topTest(void) {
	printTitle("Top");

	std::cout << "construct empty stk:\n";
	__NS__::stack<int> stk;
	printSize(stk);

	std::cout << "+ 2 4\n";
	stk.push(2);
	stk.push(4);
	std::cout << "top: " << stk.top() << std::endl;
	printSize(stk);
}

/**
 * @brief push/pop test
 */

void	pbTest(void) {
	printTitle("Push/Pop");

	std::cout << "construct empty stk:\n";
	__NS__::stack<int> stk;
	printSize(stk);

	std::cout << "+ 1\n";
	stk.push(1);
	printSize(stk);

	std::cout << "- 1\n";
	stk.pop();
	printSize(stk);

	std::cout << "+ 1\n";
	stk.push(1);
	std::cout << "top: " << stk.top() << std::endl;
	printSize(stk);

	std::cout << "+ 2\n";
	stk.push(2);
	std::cout << "top: " << stk.top() << std::endl;
	printSize(stk);

	std::cout << "+ 3\n";
	stk.push(3);
	std::cout << "top: " << stk.top() << std::endl;
	printSize(stk);

	std::cout << "- 3\n";
	stk.pop();
	std::cout << "top: " << stk.top() << std::endl;
	printSize(stk);

	std::cout << "- 2\n";
	stk.pop();
	std::cout << "top: " << stk.top() << std::endl;
	printSize(stk);

	std::cout << "- 1\n";
	stk.pop();
	printSize(stk);
}

/**
 * @brief main
 */

int main(int ac, char **av) {
	if (ac == 1) {
		printTitle("Args help");
		
		std::cout << "- \033[1;36mall\033[0m: launch all test\n"
			<< "- \033[1;36mconstructTest\033[0m: launch about constructor test\n"
			<< "- \033[1;36memptyTest\033[0m: launch about empty test\n"
			<< "- \033[1;36msizeTest\033[0m: launch about size/max_size/capacity test\n"
			<< "- \033[1;36mtopTest\033[0m: launch about top test\n"
			<< "- \033[1;36mpbTest\033[0m: launch about push/pop test\n";
		return 0;
	}

	Test test[] = {
		{"constructTest", &constructTest},
		{"emptyTest", &emptyTest},
		{"sizeTest", &sizeTest},
		{"topTest", &topTest},
		{"pbTest", &pbTest}};

	if (std::string(av[1]) == "all") {
		for (int i = 0; i < 5; i++)
			test[i].fptr();
		return 0;
	}

	std::string arg(av[1]);
	for (int i = 0; i < 5; i++) {
		if (test[i].testName == arg) {
			test[i].fptr();
			return 0;
		}
	}

	return 1;
}