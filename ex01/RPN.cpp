/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:44:59 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/12/17 11:35:05 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

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

int RPN::ans(long num1, long num2, char sign) {
    static long ans;
	if (sign == '+')
		ans = num1 + num2;
	else if (sign == '-')
		ans = num2 - num1;
	else if (sign == '*')
		ans = num1 * num2;
	else
		ans = num2 / num1;
	
    if (ans > 2147483647 || ans < -2147483648)
	{
		throw std::invalid_argument("Error: answer is out of range");	
	}
    return static_cast<int>(ans);
}

void RPN::check_input(char **av) {
    std::string str = av[1];
    std::istringstream iss(str);
    std::string token;
    
    const long long INT_MAX_LL = std::numeric_limits<int>::max();
    const long long INT_MIN_LL = std::numeric_limits<int>::min();
    
    while (iss >> token) {
        // 演算子の場合はスキップ
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            continue;
        }
        
        // 数字の場合のみチェック
        if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && std::isdigit(token[1]))) {
            // long longに変換してオーバーフローをチェック
            char *endptr;
            long long num = std::strtoll(token.c_str(), &endptr, 10);
            
            // 変換エラーのチェック
            if (*endptr != '\0') {
                throw std::invalid_argument("Error: invalid number format");
            }

            // オーバーフローチェック
            if (num > INT_MAX_LL || num < INT_MIN_LL) {
                throw std::invalid_argument("Error: number is out of int range");
            }
        }
    }
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
			int a = ans(static_cast<long>(num1), static_cast<long>(num2), *it);
			_data.push(a);
		}
		else
			throw std::invalid_argument("Error");
	}
	if (_data.size() > 1)
		throw std::invalid_argument("Error: Argument error");
	std::cout << _data.top() << std::endl;
}