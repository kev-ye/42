/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:36:45 by kaye              #+#    #+#             */
/*   Updated: 2021/09/09 20:49:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(void) {}

TargetGenerator::~TargetGenerator(void) {
	std::vector<ATarget*>::iterator it = this->_target.begin();
	std::vector<ATarget*>::iterator ite = this->_target.end();

	for (; it != ite; it++) {
		delete *it;
	}
	this->_target.clear();
}

void	TargetGenerator::learnTargetType(ATarget *target) {
	std::vector<ATarget*>::iterator it = this->_target.begin();
	std::vector<ATarget*>::iterator ite = this->_target.end();

	for (; target && it != ite; it++) {
		if ((*it)->getType() == target->getType())
			return ;
	}
	this->_target.push_back(target->clone());
}

void	TargetGenerator::forgetTargetType(std::string const & targetType) {
	std::vector<ATarget*>::iterator it = this->_target.begin();
	std::vector<ATarget*>::iterator ite = this->_target.end();

	for (; it != ite; it++) {
		if ((*it)->getType() == targetType) {
			delete *it;
			this->_target.erase(it);
			return ;
		}
	}
}

ATarget*	TargetGenerator::createTarget(std::string const & targetType) {
	std::vector<ATarget*>::iterator it = this->_target.begin();
	std::vector<ATarget*>::iterator ite = this->_target.end();

	for (; it != ite; it++) {
		if ((*it)->getType() == targetType)
			return *it;
	}
	return NULL;
}