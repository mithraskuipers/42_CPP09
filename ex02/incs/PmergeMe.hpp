/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/20 17:44:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstddef>

#define START(x) x + 1

class PmergeMe
{
public:
	// Orthodox Canonical Form
	PmergeMe();
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &other);
	PmergeMe(const PmergeMe &other);

	// Vector sort functions
	static void fordJohnsonVector(std::vector<int> &container, int start, int end);
	static void mergeSortVector(std::vector<int> &container, int start, int mid, int end);
	static void insertSortVector(std::vector<int> &container, int start, int end);

	// Deque sort functions
	static void fordJohnsonDeque(std::deque<int> &container, int start, int end);
	static void mergeSortDeque(std::deque<int> &container, int start, int mid, int end);
	static void insertSortDeque(std::deque<int> &container, int start, int end);

	// Utility functions
	void printVector(const std::vector<int> &vectorContainer, bool isBefore);
	void printDeque(const std::deque<int> &dequeContainer, bool isBefore);
	static void wrapper(std::vector<int> &, std::deque<int> &, uint &, uint &);
	static int findSplitIndex(int start, int end);
	static int jacobsthal(int n);
};

#endif
