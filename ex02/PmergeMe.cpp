/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:33:22 by kawaharadar       #+#    #+#             */
/*   Updated: 2025/11/20 14:33:48 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//utils
int j_num(int num) {
	int ans = static_cast<int>(std::pow(2, num));
	if (num % 2 == 0)
		ans -= 1;
	else
		ans += 1;
	return (ans / 3);
}

int	j_gap(int num) {
	return (j_num(num) - j_num(num - 1));
}

//convert string to int and check error
int	ft_num(char *str) {
	long ans = 0;
	for (size_t i = 0; str[i]; i++) {
		if (!std::isdigit(str[i]))
			throw std::invalid_argument("Error: number must be int");
		ans = ans * 10 + (str[i] - '0');
	}
	if (ans > (long)2147483647)
		throw std::invalid_argument("Error: number must be in 0 - 2147483647");
	return (ans);
}

//checking deque list function
void check_deque(std::deque<pairs> p) {
	size_t	i = 0;
	size_t l = 0;
	while (i < p.size() - 1) {
		l = i + 1;
		while (l < p.size()) {
			if (p.at(i).num == p.at(l).num)
				throw std::invalid_argument("Error: numbers must be different");
			l++;
		}
		i++;
	}
}

//checking vector list function
void check_vector(std::vector<pairs> p) {
	size_t	i = 0;
	size_t l = 0;
	while (i < p.size() - 1) {
		l = i + 1;
		while (l < p.size()) {
			if (p.at(i).num == p.at(l).num)
				throw std::invalid_argument("Error: numbers must be different");
			l++;
		}
		i++;
	}
}

//creating deque container functions
std::deque<pairs> create_deque(char **av) {
	std::deque<pairs> ans;

	for (size_t i = 1; av[i]; i++) {
		pairs node;
		node.num = ft_num(av[i]);
		ans.push_back(node);
	}
	check_deque(ans);
	return (ans);
}

//creating vector container functions
std::vector<pairs> create_vector(char **av) {
	std::vector<pairs> ans;

	for (size_t i = 1; av[i]; i++) {
		pairs node;
		node.num = ft_num(av[i]);
		ans.push_back(node);
	}
	check_vector(ans);
	return ans;
}

//sorting deque functions

std::deque<pairs> binary_sort_deque(std::deque<pairs> big, pairs p) {
    int right = static_cast<int>(big.size()) - 1;
    int left = 0;
    int mid;
    while (left <= right) {
        mid = (right + left) / 2;
        if (big[mid].num < p.num)
            left = mid + 1;
        else
            right = mid - 1;
    }
    big.insert(big.begin() + left, p);
    return (big);
}

std::vector<pairs> binary_sort_vector(std::vector<pairs> big, pairs p) {
    int right = static_cast<int>(big.size()) - 1;
    int left = 0;
    int mid;
    while (left <= right) {
        mid = (right + left) / 2;
        if (big[mid].num < p.num)
            left = mid + 1;
        else
            right = mid - 1;
    }
    big.insert(big.begin() + left, p);
    return (big);
}

std::deque<pairs> deq_systematization(std::deque<pairs> deq) {
    //要素数1の時はそのまま返す
	if (deq.size() == 1)
		return (deq);
    //要素数2の時は大小関係を確認して返す
	if (deq.size() == 2) {
		if (deq[0].num > deq[1].num)
			std::swap(deq[0], deq[1]);
		return (deq);
	}
    //要素数3以上の時
    //小さい方をペアに大き方のをペアに入れてbigに入れる
    std::deque<pairs> big;
    std::deque<pairs> small;
    for (size_t i = 0; i < deq.size() - 1; i += 2) {
        if (deq[i].num < deq[i + 1].num) {
            deq[i + 1].p.push_back(deq[i]);
            big.push_back(deq[i + 1]);
        } else {
            deq[i].p.push_back(deq[i + 1]);
            big.push_back(deq[i]);
        }
    }
    //再起に入れてsortされたものが返ってくるはず
    big = deq_systematization(big);
    //smallにbigのペアを順番に入れていく
    for (size_t i = 0; i < big.size(); i++) {
        small.push_back(big[i].p.back());
        big[i].p.pop_back();
    }
    //余りの処理
    if (deq.size() % 2 == 1)
        small.push_back(deq.back());
    //smallの先頭は確定でbigの先頭卍
    if (small.size() > 0) {
        big.push_front(small.front());
        small.pop_front();
    }

    int i = 3;
    while (small.size() > 0) {
        int index = j_gap(i);
        if (static_cast<size_t>(index) > small.size())
            index = static_cast<int>(small.size());
        
        // 後ろから前に処理することで、削除によるインデックスのずれを防ぐ
        for (int j = index - 1; j >= 0; j--) {
            big = binary_sort_deque(big, small[j]);
            small.erase(small.begin() + j);
        }
        i++;
    }
    return (big);
}

std::vector<pairs> vec_systematization(std::vector<pairs> vec) {
    //要素数1の時はそのまま返す
	if (vec.size() == 1)
		return (vec);
    //要素数2の時は大小関係を確認して返す
	if (vec.size() == 2) {
		if (vec[0].num > vec[1].num)
			std::swap(vec[0], vec[1]);
		return (vec);
	}
    //要素数3以上の時
    //小さい方をペアに大き方のをペアに入れてbigに入れる
    std::vector<pairs> big;
    std::vector<pairs> small;
    for (size_t i = 0; i < vec.size() - 1; i += 2) {
        if (vec[i].num < vec[i + 1].num) {
            vec[i + 1].p.push_back(vec[i]);
            big.push_back(vec[i + 1]);
        } else {
            vec[i].p.push_back(vec[i + 1]);
            big.push_back(vec[i]);
        }
    }
    //再起に入れてsortされたものが返ってくるはず
    big = vec_systematization(big);
    //smallにbigのペアを順番に入れていく
    for (size_t i = 0; i < big.size(); i++) {
        small.push_back(big[i].p.back());
        big[i].p.pop_back();
    }
    //余りの処理
    if (vec.size() % 2 == 1)
        small.push_back(vec.back());
    //smallの先頭は確定でbigの先頭卍
    if (small.size() > 0) {
        big.insert(big.begin(), small.front());
        small.erase(small.begin());
    }

    int i = 3;
    while (small.size() > 0) {
        int index = j_gap(i);
        if (static_cast<size_t>(index) > small.size())
            index = static_cast<int>(small.size());
        
        // 後ろから前に処理することで、削除によるインデックスのずれを防ぐ
        for (int j = index - 1; j >= 0; j--) {
            big = binary_sort_vector(big, small[j]);
            small.erase(small.begin() + j);
        }
        i++;
    }
    return (big);
}