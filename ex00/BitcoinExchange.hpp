/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:13:28 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/12/29 01:24:01 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

class BitcoinExchange {
	private: 
		std::map <std::string, double> _data;

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		bool checkData(std::string& str);
		bool checkDay(std::string& year, std::string& month, std::string& day);
		bool checkRate(std::string& rate);

	public:
		BitcoinExchange(const std::string& inputfile);
		~BitcoinExchange();
		void analyze(const std::string &file);
		double findRate(std::string& date);

	//exception
	class CantOpenDataFileException : public std::exception {
		public :
			virtual const char* what() const throw();
	};

	class CantOpenInfileException : public std::exception {
		public :
			virtual const char* what() const throw();
	};

	class NoValidDataException : public std::exception {
		public :
			virtual const char* what() const throw();
	};

	class InfileFormatErrorException : public std::exception {
		public :
			virtual const char* what() const throw();
	};

	//debug
	void print_data();
};