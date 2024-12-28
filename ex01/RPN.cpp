/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:44:59 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/12/29 03:16:03 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		*this = other;
	}
	return *this;
}

RPN::RPN(const RPN& other) {
	*this = other;
}

RPN::RPN() {};

RPN::~RPN() {};

int RPN::ans(int num1, int num2, char sign) {
	if (sign == '+')
		return (num1 + num2);
	else if (sign == '-')
		return (num1 - num2);
	else if (sign == '*')
		return (num1 * num2);
	else
		return (num1 / num2);
}

void RPN::calculate(std::string str) {
	if (str.empty())
		throw std::invalid_argument("Error: argument is empty.");
	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		if (std::isspace(*it))
			continue ;
		else if (std::isdigit(*it)) {
			_data.push((*it) - '0');
		}
		else if (*it == '-' || *it == '*' || *it == '/' || *it == '+') {
			if (_data.size() < 2)
				throw std::invalid_argument("Error: calculate error");
			int num1 = _data.top();
			_data.pop();
			int num2 = _data.top();
			_data.pop();
			int a = ans(num2, num1, *it);
			_data.push(a);
		}
		else
			throw std::invalid_argument("Error");
	}
	if (_data.size() > 1)
		throw std::invalid_argument("Error: Argument error");
	std::cout << _data.top() << std::endl;
}