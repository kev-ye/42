/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:23:33 by kaye              #+#    #+#             */
/*   Updated: 2021/09/10 18:04:58 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATARGET_HPP
# define ATARGET_HPP

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class ATarget {
	public:
		ATarget(void);
		ATarget(std::string const &);
		ATarget(ATarget const &);
		virtual ~ATarget(void);

		ATarget & operator=(ATarget const &);

	public:
		std::string const & getType(void) const;
		void getHitBySpell(ASpell const &) const;
	
		virtual ATarget *clone(void) = 0;

	protected:
		std::string _type;	
};

#endif