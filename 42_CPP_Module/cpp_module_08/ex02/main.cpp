/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 13:02:51 by kaye              #+#    #+#             */
/*   Updated: 2021/09/08 18:29:41 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutantstack.hpp"
#include <list>

void test1(void) {
	std::cout << "\e[1;32m- MutantStack test -\e[0m" << std::endl;
	MutantStack<int> mstack;
	
	mstack.push(5);
	mstack.push(17);
	
	std::cout << "Top: " << mstack.top() << std::endl;

	mstack.pop();

	std::cout << "Size: " << mstack.size() << std::endl;
	
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	std::cout << "MutantStack:";
	while (it != ite) {
		std::cout << ' ' << *it;
		++it;
	}
	std::cout << std::endl;

	std::stack<int> s(mstack);

	std::cout << "Stack(assign):";
	while (!s.empty()) {
		std::cout << ' ' << s.top();
		s.pop();
	}
	std::cout << std::endl;

	std::cout << std::endl;
}

void test2(void) {
	std::cout << "\e[1;32m- List test -\e[0m" << std::endl;
	std::list<int> l;
	
	l.push_back(5);
	l.push_back(17);
	
	std::cout << "Top: " << l.back() << std::endl;

	l.pop_back();

	std::cout << "Size: " << l.size() << std::endl;
	
	l.push_back(3);
	l.push_back(5);
	l.push_back(737);
	//[...]
	l.push_back(0);
	
	std::list<int>::iterator it = l.begin();
	std::list<int>::iterator ite = l.end();

	++it;
	--it;
	std::cout << "list:";
	while (it != ite) {
		std::cout << ' ' << *it;
		++it;
	}
	std::cout << std::endl;

	std::cout << std::endl;
}

void test3(void) {
	std::cout << "\e[1;32m- stack + iterator full test -\e[0m" << std::endl;

	/* constructor */
	MutantStack<int> mutantstack;

	/* empty */
	if (mutantstack.empty() == true)
		std::cout << "mutantstack is empty" << std::endl;

	/* size */
	std::cout << "mutantstack size: " << mutantstack.size() << std::endl;

	/* push */
	mutantstack.push(1);

	/* top */
	std::cout << "mutantstack top: " << mutantstack.top() << std::endl;

	/* pop */
	mutantstack.pop();

	mutantstack.push(1);
	mutantstack.push(2);
	mutantstack.push(3);

	/* iterator begin + end */
	MutantStack<int>::iterator it = mutantstack.begin();
	std::cout << "iterator begin + end:";
	for (; it != mutantstack.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	/* iterator rbegin + rend */
	MutantStack<int>::reverse_iterator rit = mutantstack.rbegin();
	std::cout << "iterator rbegin + rend:";
	for (; rit != mutantstack.rend(); rit++)
		std::cout << ' ' << *rit;
	std::cout << std::endl;
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}