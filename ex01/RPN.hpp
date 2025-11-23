/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:45:02 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/11/23 14:00:34 by kawaharadar      ###   ########.fr       */
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
		int ans(int num1, int num2, char sign);

	public:
		RPN();
		~RPN();
		void calculate(std::string str);
        static void check_input(char **av);
};