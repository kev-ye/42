/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:38:29 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:47:33 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int main() {
	Karen karen;

	karen.complain("DEBUG");
	karen.complain("debug");

	karen.complain("INFO");
	karen.complain("info");

	karen.complain("WARNING");
	karen.complain("warning");

	karen.complain("ERROR");
	karen.complain("error");
	return (0);
}