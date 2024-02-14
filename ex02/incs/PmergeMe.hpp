/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/14 20:48:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <vector>
#include <iterator>

class PmergeMe
{
	private:
		std::list<int> mList;
		std::deque<int> mDeque;
		size_t size;

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(std::list<int> _list, std::deque<int> _deque);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);

		size_t isStringOnlyDigits(const char *s);
		void takeArgs(int argc, char **argv);
		template <typename T>
		void insertionSort(T &A, int p, int r);
		void printTime(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> end, const std::string &type);

		void mergeMe(int argc, char **argv);
		template <typename T>
		void printSortedInput(const T &A);

	private:
		template <typename T>
		void mergeInsert(T &A, typename T::iterator p, typename T::iterator r);
		template <typename T>
		void merge(T &A, typename T::iterator p, typename T::iterator q, typename T::iterator r);
};

#endif
