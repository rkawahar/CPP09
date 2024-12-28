/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:45:02 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/12/29 03:04:28 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>

class RPN {
	private:
		RPN& operator=(const RPN& other);
		RPN(const RPN& other);
		std::stack<int> _data;
		int ans(int num1, int num2, char sign);

	public:
		RPN();
		~RPN();
		void calculate(std::string str);
};