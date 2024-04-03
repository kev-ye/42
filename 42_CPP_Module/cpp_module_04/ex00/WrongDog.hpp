/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongDog.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:45:38 by kaye              #+#    #+#             */
/*   Updated: 2021/08/07 14:20:35 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGDOG_HPP
# define WRONGDOG_HPP

#include "WrongAnimal.hpp"

class WrongDog : public WrongAnimal {
	public:
		WrongDog(void);
		WrongDog(WrongDog const & src);
		virtual ~WrongDog(void);

		WrongDog & operator=(WrongDog const & rhs);
	
	public:
		void	makeSound(void) const;
};

#endif