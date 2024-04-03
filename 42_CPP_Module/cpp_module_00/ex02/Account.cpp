/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:43:00 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:45:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit) :
	_accountIndex(Account::_nbAccounts),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0) {

	Account::_nbAccounts++;
	Account::_totalAmount += this->_amount;

	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ';' \
		<< "amount:" << this->_amount << ';' \
		<< "created" << std::endl; 
	return ;
}

Account::~Account(void) {
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ';' \
		<< "amount:" << this->_amount << ';' \
		<< "closed" << std::endl;
	return ;
}

int 	Account::getNbAccounts(void) {
	return (Account::_nbAccounts);
}

int		Account::getTotalAmount(void) {
	return (Account::_totalAmount);
}

int		Account::getNbDeposits(void) {
	return (Account::_totalNbDeposits);
}

int		Account::getNbWithdrawals(void) {
	return (Account::_totalNbWithdrawals);
}

void	Account::displayAccountsInfos(void) {
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() << ';' \
		<< "total:" << Account::getTotalAmount() << ';' \
		<< "deposits:" << Account::getNbDeposits() << ';' \
		<< "withdrawals:" << Account::getNbWithdrawals() << std::endl;
}

void	Account::makeDeposit(int deposit) {
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ';' \
		<< "p_amout:" << this->_amount << ';' \
		<< "deposits:" << deposit << ';';
	
	this->_nbDeposits = 1;
	this->_amount += deposit;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits += this->_nbDeposits;
	std::cout << "amout:" << this->_amount << ';' \
		<< "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal) {
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ';' \
		<< "p_amount:" << this->_amount << ';';

	if (withdrawal > this->checkAmount()) {
		this->_nbWithdrawals = 0;
		std::cout << "withdrawal:refused" << std::endl;
		return (false);
	}
	
	std::cout << "withdrawl:" << withdrawal << ';';

	this->_nbWithdrawals = 1;
	this->_amount -= withdrawal;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals += this->_nbWithdrawals;
	std::cout << "amount:" << this->_amount << ';' \
		<< "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
	return (true);
}

int		Account::checkAmount(void) const {
	return (this->_amount);
}

void	Account::displayStatus(void) const {
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ';' \
		<< "amount:" << this->_amount << ';' \
		<< "deposits:" << this->_nbDeposits << ';' \
		<< "withdrawals:" << this->_nbWithdrawals<< std::endl; 
}

void	Account::_displayTimestamp(void) {
	const time_t	now = time(0);
	const tm		*ltm = localtime(&now);
	
	std::cout << '[';

	// date
	std::cout << 1900 + ltm->tm_year;
	if ((ltm->tm_mon + 1) < 10)
		std::cout << '0';
	std::cout << ltm->tm_mon + 1;
	if (ltm->tm_mday < 10)
		std::cout << '0';
	std::cout << ltm->tm_mday;

	std::cout << '_';

	// time
	if (ltm->tm_hour < 10)
		std::cout << '0';
	std::cout << ltm->tm_hour;
	if (ltm->tm_min < 10)
		std::cout << '0';
	std::cout << ltm->tm_min;
	if (ltm->tm_sec < 10)
		std::cout << '0';
	std::cout << ltm->tm_sec;

	std::cout << "] ";
}