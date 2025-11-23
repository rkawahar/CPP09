/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:30:29 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/11/23 16:39:32 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>

int main(int ac, char **av) {
    if (ac < 2) {
		std::cerr << "Argument Error" << std::endl;
		return 1;
	}
	try {
		std::deque<pairs> deq = create_deque(av);
		std::vector<pairs> vec = create_vector(av);
		
		// deque処理時間の計測
		struct timeval start_deq, end_deq;
		gettimeofday(&start_deq, NULL);
		deq = deq_systematization(deq);
		gettimeofday(&end_deq, NULL);
		long deq_time = (end_deq.tv_sec - start_deq.tv_sec) * 1000000 + (end_deq.tv_usec - start_deq.tv_usec);
		
		// vector処理時間の計測
		struct timeval start_vec, end_vec;
		gettimeofday(&start_vec, NULL);
        vec = vec_systematization(vec);
		gettimeofday(&end_vec, NULL);
		long vec_time = (end_vec.tv_sec - start_vec.tv_sec) * 1000000 + (end_vec.tv_usec - start_vec.tv_usec);
        //before
        std::cout << "before: ";
        for (int i = 1; i < ac; i++){
            std::cout << av[i] << " ";
        }
        std::cout << std::endl;
        //after
        std::cout << "deque after: ";
        for (size_t i = 0; i < deq.size(); i++) {
            std::cout << deq[i].num << " ";
        }
        std::cout << std::endl;
        std::cout << "vector after: ";
        for (size_t i = 0; i < vec.size(); i++) {
            std::cout << vec[i].num << " ";
        }
        std::cout << std::endl;
        
        // 処理時間の表示
        std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " 
                  << deq_time << " us" << std::endl;
        std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " 
                  << vec_time << " us" << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}