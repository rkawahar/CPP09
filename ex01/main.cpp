/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:44:57 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/12/29 02:49:12 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Invalid argument: you must write two argument" << std::endl;
		return 1;
	}
	try {
		RPN cal;
		cal.calculate(av[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}