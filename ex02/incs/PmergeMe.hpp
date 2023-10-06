/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/06 18:40:13 by mikuiper      ########   odam.nl         */
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
		
		void fordJohnsonSort(char **argv);
		std::vector<int> intVector;
		std::deque<int> intDeque;
		void intVectorPrinter();
		void intDequePrinter();
};

#endif
