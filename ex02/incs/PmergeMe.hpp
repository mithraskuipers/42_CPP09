/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/01/03 21:58:37 by mikuiper      ########   odam.nl         */
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
		void setPrintOutput(bool enablePrint);
		template<typename T>
		void fordJohnsonSort(T &lst, int lst_start_idx, int lst_end_idx);
		void fordJohnsonSortWrapper();
		template<typename T>
		void mergeSublists(T &lst, int lst_start_idx, int mid, int lst_end_idx);
};

#endif
