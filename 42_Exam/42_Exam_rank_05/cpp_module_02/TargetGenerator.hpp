/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:36:12 by kaye              #+#    #+#             */
/*   Updated: 2021/09/10 18:05:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

#include "ATarget.hpp"
#include <iostream>
#include <vector>
#include <iterator>

class TargetGenerator {
	public:
		TargetGenerator(void);
		virtual ~TargetGenerator(void);

	private:
		TargetGenerator(TargetGenerator const &);
		TargetGenerator & operator=(TargetGenerator const &);

	public:
		void	learnTargetType(ATarget *);
		void	forgetTargetType(std::string const &);
		ATarget*	createTarget(std::string const &);

	private:
		std::vector<ATarget*> _target;
};

#endif