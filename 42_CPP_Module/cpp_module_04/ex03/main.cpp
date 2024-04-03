/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 12:57:40 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:23:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

void test1() {
	std::cout << "\e[1;32m- Basic test -\e[0m\n" << std::endl;

	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	std::cout << std::endl;

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << std::endl;
}

void test2() {
	std::cout << "\e[1;32m- Deep copy test -\e[0m\n" << std::endl;
	
	Character		*player1 = new Character("player1");
	MateriaSource	*src = new MateriaSource();
	AMateria		*tmp;

	src->learnMateria(new Ice());
	tmp = src->createMateria("ice");
	player1->equip(tmp);
	tmp = src->createMateria("ice");
	player1->equip(tmp);
	src->learnMateria(new Cure());
	tmp = src->createMateria("cure");
	player1->equip(tmp);
	tmp = src->createMateria("cure");
	player1->equip(tmp);

	std::cout << std::endl;
	std::cout << "\e[1;32mCOPY: player2 = *player2\e[0m" << std::endl;
	Character	player2;
	player2 = *player1;

	std::cout << "player1: " << std::endl;
	player1->use(0, *player1);
	player1->use(1, *player1);
	player1->use(2, *player1);
	player1->use(3, *player1);

	std::cout << "player2: " << std::endl;
	player2.use(0, player2);
	player2.use(1, player2);
	player2.use(2, player2);
	player2.use(3, player2);

	std::cout << std::endl;
	std::cout << "\e[1;32mCHANGE: unequip [2] and [3] of player1\e[0m" << std::endl;

	player1->unequip(2);
	player1->unequip(3);

	std::cout << "player1: " << std::endl;
	player1->use(0, *player1);
	player1->use(1, *player1);
	player1->use(2, *player1);
	player1->use(3, *player1);

	std::cout << "player2: " << std::endl;
	player2.use(0, player2);
	player2.use(1, player2);
	player2.use(2, player2);
	player2.use(3, player2);

	delete player1;
	delete src;

	std::cout << std::endl;
}


void test3() {
	std::cout << "\e[1;32m- full case test -\e[0m\n" << std::endl;

	ICharacter* unknow = new Character();
	ICharacter* player1 = new Character("player1");
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Cure());
	src->learnMateria(new Cure());

	AMateria* tmp1 = src->createMateria("ice");
	unknow->equip(tmp1);
	AMateria* tmp2 = src->createMateria("ice");
	unknow->equip(tmp2);
	AMateria* tmp3 = src->createMateria("cure");
	unknow->equip(tmp3);
	AMateria* tmp4 = src->createMateria("cure");
	unknow->equip(tmp4);
	AMateria* tmp5 = src->createMateria("cure");
	unknow->equip(tmp5);

	std::cout << std::endl;

	unknow->use(0, *player1);
	unknow->use(1, *player1);
	unknow->use(2, *player1);
	unknow->use(3, *player1);
	unknow->use(4, *player1);

	delete unknow;
	delete player1;
	delete src;
	delete tmp5;

	std::cout << std::endl;
}

void test4() {
	std::cout << "\e[1;32m- unknow materia case test -\e[0m\n" << std::endl;

	ICharacter* unknow = new Character();
	ICharacter* player1 = new Character("player1");
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	AMateria* tmp;
	tmp = src->createMateria("ice");
	unknow->equip(tmp);
	tmp = src->createMateria("cure");
	unknow->equip(tmp);
	tmp = src->createMateria("unknow");
	unknow->equip(tmp);
	tmp = src->createMateria("anything");
	unknow->equip(tmp);

	std::cout << std::endl;

	unknow->use(0, *player1);
	unknow->use(1, *player1);
	unknow->use(2, *player1);
	unknow->use(3, *player1);

	delete unknow;
	delete player1;
	delete src;
}

int main()
{
	test1();
	test2();
	test3();
	test4();

#if defined(__APPLE__) && defined(__MACH__)
	/* show if leaks */
	std::cout << "\e[1;32m- if leaks ... -\e[0m\n" << std::endl;
	system("leaks interface_recap");
#endif
	return 0;
}