/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:19:14 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 20:21:03 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int main(int ac, char **av) {
	if (ac != 4) {
		std::cerr << "usage : ./replace [filename] [s1] [s2]" << std::endl;
		return (1);
	}

	std::string s1(av[2]);
	std::string s2(av[3]);
	if (s1.empty() == true || s2.empty() == true) {
		std::cerr << "s1 or s2 can't be empty" << std::endl;
		return (1);
	}

	std::string filename(av[1]);
	std::string to_replace(filename);
	to_replace += ".replace";

	std::ifstream ifs(filename.c_str());
	if (!ifs.is_open()) {
		std::cerr << "open [" << filename << "] failed !" << std::endl;
		return (1);
	}

	std::ofstream ofs(to_replace.c_str());
	if (!ofs.is_open()) {
		std::cerr << "open [" << to_replace << "] failed !" << std::endl;
		return (1);
	}

	std::string contents;
	std::string::size_type pos;
	do {
		std::getline(ifs, contents);
	
		do {
			if ((pos = contents.find(s1)) == std::string::npos) {
				ofs << contents;
				break ;
			}
			else {
				contents.erase(pos, s1.length());
				contents.insert(pos, s2);
			}
		} while (true);

		if (ifs.eof() == true)
			break ;
		else
			ofs << std::endl;
	} while (true);
	

	ifs.close();
	ofs.close();
	return (0);
}