/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:44:57 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/11/23 13:54:01 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Invalid argument: you must write two argument" << std::endl;
		return 1;
	}
	try {
		RPN::check_input(av);
		RPN cal;
		cal.calculate(av[1]);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}