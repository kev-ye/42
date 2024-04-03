/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:18:04 by kaye              #+#    #+#             */
/*   Updated: 2021/08/10 17:54:11 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CHARACTER_HPP
# define CHARACTER_HPP

#include "ICharacter.hpp"

#define INVENTORY 4

class Character : public ICharacter {
	public:
		Character(void);
		Character(std::string const & name);
		Character(Character const & src);
		virtual ~Character(void);

		Character &	operator=(Character const & rhs);
	
	public:
		std::string	const &	getName(void) const;
		void				equip(AMateria *m);
		void				unequip(int idx);
		void				use(int idx, ICharacter & target);

		AMateria 			*getInventoryMateria(int idx) const;

	private:
		std::string	_name;
		AMateria	*_m[INVENTORY];
		AMateria	*_bag[INVENTORY];
};

#endif