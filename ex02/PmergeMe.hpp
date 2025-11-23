/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:32:56 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/11/23 18:17:38 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP


# include <iostream>
# include <deque>
# include <vector>
# include <cmath>

struct pairs {
	int num;
	std::vector<pairs> p;
};

std::deque<pairs> create_deque(char **av);
std::vector<pairs> create_vector(char **av);
std::deque<pairs> deq_systematization(std::deque<pairs> deq);
std::vector<pairs> vec_systematization(std::vector<pairs> vec);
int ft_num(char *str);

#endif