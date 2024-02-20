/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/20 11:58:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
NOTE: THIS CPP09 EX02 IMPLEMENTATION USES:
(1) std::list
(2) std::deque
*/

/*
make re ; ./PmergeMe $(shuf -i 10-100 -n 30) ;
make re ; ./PmergeMe $(shuf -i 1-100000 -n 3000) ;

For explanations:
make re ; ./PmergeMe 4 1 3 2 8 ;
*/

/*
SOURCE:
https://en.wikipedia.org/wiki/Merge-insertion_sort
*/

#include "../incs/PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>

int main(int argc, char **argv)
{
	try
	{
		if (argc < 2)
			throw ": Enter args";

		// Initialize containers
		std::vector<int> vectorContainer;
		std::deque<int> dequeContainer;
		double vectorSortingTime;
		double dequeSortingTime;
		int number;

		// Populate containers from command line arguments
		for (int index = 1; index < argc; index++)
		{
			std::stringstream readstring(argv[index]);
			if (!(readstring >> number) || !(readstring.eof()))
			{
				throw "";
			}
			if (number < 0)
			{
				throw ": Negative number !";
			}
			vectorContainer.push_back(number);
			dequeContainer.push_back(number);
		}

		// Print initial state
		PmergeMe::print(vectorContainer, dequeContainer);

		// Calculate sorting time
		PmergeMe::trackTime(vectorContainer, dequeContainer, vectorSortingTime, dequeSortingTime);

		// Print sorted state and sorting times
		PmergeMe::print(vectorContainer, dequeContainer);
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << vectorSortingTime << " us" << std::endl;
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque :  " << dequeSortingTime << " us" << std::endl;
	}
	catch (const char *errorMsg)
	{
		std::cout << "Error " << errorMsg << std::endl;
	}
	return 0;
}
