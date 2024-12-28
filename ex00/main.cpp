/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:18:10 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/12/29 00:39:46 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char** av) {
	if (ac != 2)
	{
		std::cerr << "Arguments Error: Arguments must be just a input file name." << std::endl;
		return 1;
	}
	try {
		BitcoinExchange coinbase("data.csv");
		// coinbase.print_data();
		coinbase.analyze(av[1]);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}