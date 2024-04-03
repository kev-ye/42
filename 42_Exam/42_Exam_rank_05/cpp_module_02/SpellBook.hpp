/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:14:15 by kaye              #+#    #+#             */
/*   Updated: 2021/09/10 18:05:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

#include "ASpell.hpp"
#include "Fwoosh.hpp"
#include "Fireball.hpp"
#include "Polymorph.hpp"
#include <iostream>
#include <exception>
#include <vector>
#include <iterator>

class SpellBook {
	public:
		SpellBook(void);
		virtual ~SpellBook(void);

	private:
		SpellBook(SpellBook const &);
		SpellBook & operator=(SpellBook const &);

	public:
		void	learnSpell(ASpell *);
		void	forgetSpell(std::string const &);
		ASpell*	createSpell(std::string const &);

	private:
		std::vector<ASpell*> _spell;
};

#endif