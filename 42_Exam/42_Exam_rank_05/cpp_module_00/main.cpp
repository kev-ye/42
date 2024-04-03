/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:40:41 by kaye              #+#    #+#             */
/*   Updated: 2021/09/09 15:48:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

int main(void) {
	// {
	// 	// Warlock bob;                            //Does not compile
	// 	Warlock bob("Bob", "the magnificent");  //Compiles
	// 	Warlock jim("Jim", "the nauseating");   //Compiles
	// 	// bob = jim;                              //Does not compile
	// 	// Warlock jack(jim);                      //Does not compile
	// }
	{
		Warlock const richard("Richard", "Mistress of Magma");
		richard.introduce();
		std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

		Warlock* jack = new Warlock("Jack", "the Long");
		jack->introduce();
		jack->setTitle("the Mighty");
		jack->introduce();

		delete jack;

		return (0);
	}
}