/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:28:02 by kaye              #+#    #+#             */
/*   Updated: 2021/08/07 19:37:27 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal {
	public:
		Animal(void);
		Animal(std::string const & type);
		Animal(Animal const & src);
		virtual ~Animal(void);

		Animal & operator=(Animal const & rhs);
	
	public:
		std::string		getType(void) const;
		virtual void	makeSound() const = 0;

	protected:
		std::string _type;
};

#endif