/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:26:35 by kaye              #+#    #+#             */
/*   Updated: 2021/08/08 12:38:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongDog.hpp"
#include "WrongCat.hpp"

int main() {
{
	std::cout << "\e[1;32m- With virtual case -\e[0m\n" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

	std::cout << "Dog: " << j->getType() << " " << std::endl;
	std::cout << "Cat: " << i->getType() << " " << std::endl;
	std::cout << "Dog:    ";
	j->makeSound();
	std::cout << "Cat:    ";
	i->makeSound(); //will output the cat sound!
	std::cout << "Animal: ";
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << std::endl;
}
{
	std::cout << "\e[1;32m- Without virtual case -\e[0m\n" << std::endl;
	const WrongAnimal* meta = new WrongAnimal();
    const WrongAnimal* j = new WrongDog();
    const WrongAnimal* i = new WrongCat();

	std::cout << "WrongDog: " << j->getType() << " " << std::endl;
	std::cout << "WrongCat: " << i->getType() << " " << std::endl;
	std::cout << "WrongDog:    ";
	j->makeSound();
	std::cout << "WrongCat:    ";
	i->makeSound();
	std::cout << "WrongAnimal: ";
	meta->makeSound();

	delete meta;
	delete j;
	delete i;
}
	return (0);
}