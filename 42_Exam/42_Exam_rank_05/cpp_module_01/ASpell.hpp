/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:54:47 by kaye              #+#    #+#             */
/*   Updated: 2021/09/10 18:04:04 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
# define ASPELL_HPP

#include "ATarget.hpp"
#include <iostream>

class ATarget;

class ASpell {
	public:
		ASpell(void);
		ASpell(std::string const &, std::string const &);
		ASpell(ASpell const &);
		virtual ~ASpell(void);

		ASpell & operator=(ASpell const &);

	public:
		std::string const & getName(void) const;
		std::string const & getEffects(void) const;
		void launch(ATarget const &);

		virtual ASpell *clone(void) const = 0;

	protected:
		std::string _name;
		std::string _effects;
};

#endif