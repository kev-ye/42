/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:45:38 by kaye              #+#    #+#             */
/*   Updated: 2021/08/07 14:14:04 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog(void);
		Dog(Dog const & src);
		virtual ~Dog(void);

		Dog & operator=(Dog const & rhs);
	
	public:
		void	makeSound(void) const;
};

#endif