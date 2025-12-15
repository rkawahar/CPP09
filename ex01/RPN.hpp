/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:45:02 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/12/15 15:26:18 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <list>
#include <string>
#include <sstream>
#include <limits>
#include <stdexcept>

class RPN {
	private:
		RPN& operator=(const RPN& other);
		RPN(const RPN& other);
		std::stack<int, std::list<int> > _data;
		int ans(long num1, long num2, char sign);

	public:
		RPN();
		~RPN();
		void calculate(std::string str);
        static void check_input(char **av);
};