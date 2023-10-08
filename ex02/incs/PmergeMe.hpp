/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/08 16:01:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <deque>

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		
		
		std::vector<int> intVector;
		std::deque<int> intDeque;
		void intVectorPrinter();
		void intDequePrinter();
		void readInput(char **argv);
		template<typename T>
		void fordJohnsonSort(T & lst, int beg, int end);
		void fordJohnsonSortWrapper();
};

#endif
