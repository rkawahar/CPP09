/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:11:03 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/12/15 14:52:51 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		*this = other;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {};

bool BitcoinExchange::checkDay(std::string& year, std::string& month, std::string& day) {
	int num_year = 0;
	for (size_t i = 0; i < year.length(); i++) {
		if (!std::isdigit(year.at(i)))
			return false;
		num_year = num_year * 10 + (year.at(i) - '0');
	}
	bool leap = false;
	if (num_year % 4 == 0)
		leap = true;
	int num_month = 0;
	int num_day = 0;
	for (size_t i = 0; i < month.length(); i++) {
		if (!std::isdigit(month.at(i)))
			return false;
		num_month = num_month * 10 + (month.at(i) - '0');
	}
	for (size_t i = 0; i < day.length(); i++) {
		if (!std::isdigit(day.at(i)))
			return false;
		num_day = num_day * 10 + (day.at(i) - '0');
	}
	if (num_month < 1 || 12 < num_month)
		return false;
	if (num_month == 4 || num_month == 6 || num_month == 9 || num_month == 11) {
		if (num_day < 1 || 30 < num_day)
			return false;
	}
	else if (num_month == 1 || num_month == 3 || num_month == 5 || num_month == 7 || num_month == 8 || num_month == 10 || num_month == 12) {
		if (num_day < 1 || 31 < num_day)
			return false;
	}
	else {
		if (leap) {
			if (num_day < 1 || 29 < num_day)
				return false;
		}
		else {
			if (num_day < 1 || 28 < num_day)
				return false;
		}
	}
	return true;
}

bool BitcoinExchange::checkData(std::string& str) {
	std::istringstream	line(str);
	std::string year, month, day, err;
	
	if (!std::getline(line, year, '-'))
		return false;
	if (!std::getline(line, month, '-'))
		return false;
	if (!std::getline(line, day, '-'))
		return false;
	if (std::getline(line, err, '-'))
		return false;
	
	int num = 0;
	for (size_t i = 0; i < year.length(); i++) {
		if (!std::isdigit(year.at(i)))
			return false;
		num = num * 10 + (year.at(i) - '0');
	}
	if (num < 2009 || 2060 < num)
		return false;
	
	return (checkDay(year, month, day));
}

bool BitcoinExchange::checkRate(std::string& rate) {
	int dot = 0;
	for (size_t i = 0; i < rate.length(); i++) {
		if (rate.at(i) == '.')
			dot++;
		else if (!std::isdigit(rate.at(i)))
			return false;
	}
	if (rate.at(rate.length() - 1) == '.' || 1 < dot)
		return false;
	return true;
}

BitcoinExchange::BitcoinExchange(const std::string& inputfile) {
	std::ifstream file(inputfile.c_str());
	if (!file)
		throw BitcoinExchange::CantOpenDataFileException();
	
	std::string line;
	std::getline(file, line);
	size_t linecount = 0;
	while (std::getline(file, line)) {
		std::string::size_type comma = line.find(',');
		linecount++;
		if (comma == std::string::npos) {
			std::cerr << "Invalid data in line " << linecount << std::endl;
			continue ;
		}
		std::string date = line.substr(0, comma);
		std::string rate = line.substr(comma + 1);
		if (!checkData(date)) {
			std::cerr << "Invalid data in line " << linecount << std::endl;
			continue ;
		}
		if (!checkRate(rate)) {
			std::cerr << "Invalid data in line " << linecount << std::endl;
			continue ;
		}
		double num;
		std::istringstream(rate) >> num;
		_data[date] = num;
	}
	file.close();
	if (_data.size() == 0)
		throw BitcoinExchange::NoValidDataException();
}

double BitcoinExchange::findRate(std::string& date) {
	std::map <std::string, double>::iterator it = _data.upper_bound(date);
	if (it != _data.begin()) {
		it--;
		return it->second;
	}
	else {
		return -1;
	}
}

void BitcoinExchange::analyze(const std::string &file) {
	std::ifstream infile(file.c_str());
	if (!infile)
		throw BitcoinExchange::CantOpenInfileException();
	std::string line;
	std::getline(infile, line);
	if (line != "date | value") {
		throw BitcoinExchange::InfileFormatErrorException();
	}
	while (std::getline(infile, line)) {
		std::istringstream stream(line);
		std::string date, value;
		char spliter;
		
		if (!(stream >> date >> spliter >> value)) {
			std::cerr << "Error: Infile format error" << std::endl;
			continue;
		}
		else if (spliter != '|') {
			std::cerr << "Error: delimiter must be '|'" << std::endl;
			continue ;
		}
		else if (!checkData(date)) {
			std::cerr << "Error: Invalid input" << std::endl;
			continue ;
		}
		else if (!checkRate(value)) {
			std::cerr << "Error: Invalid value" << std::endl;
			continue ;
		}
		double rate = findRate(date);
		if (rate < 0)
			std::cerr << "Error: no exchange rate before this date" << std::endl;
		else {
			double val;
			std::istringstream(value) >> val;
			if (val > 1000 || 0 > val) 
				std::cerr << "Error: Invalid value" << std::endl;
			else
				std::cout << date << " => " << val << " = " << rate * val << std::endl; 
		}
	}
	infile.close();
	return ;
};

//Exception

const char* BitcoinExchange::CantOpenDataFileException::what() const throw(){
	return ("Cant open the data file");
};

const char* BitcoinExchange::CantOpenInfileException::what() const throw(){
	return ("Cant open the infile");
};

const char* BitcoinExchange::NoValidDataException::what() const throw() {
	return ("No valid data");
}

const char* BitcoinExchange:: InfileFormatErrorException::what() const throw() {
	return ("Infile Format Error: write \"date | value\" in the first line.");
}

//debug
void BitcoinExchange::print_data() {
	for (std::map<std::string, double>::iterator it = _data.begin(); it != _data.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
}