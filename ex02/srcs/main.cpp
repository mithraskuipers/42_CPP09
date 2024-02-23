/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/23 21:06:33 by mikuiper      ########   odam.nl         */
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
https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort
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
		{
			throw ": Enter a list of numbers, separated by spaces";
		}
		// Initialize containers
		std::vector<int> vectorContainer;
		std::deque<int> dequeContainer;
		uint vectorSortingTime;
		uint dequeSortingTime;
		int currentNumber;
		double elapsed;
		PmergeMe merger;

		// Populate containers from command line arguments
		for (int index = 1; index < argc; index++)
		{
			std::stringstream userInput(argv[index]);
			if (!(userInput >> currentNumber) || !(userInput.eof()))
			{
				throw("Invalid input format. Please provide integer arguments only.");
			}
			if (currentNumber < 0)
			{
				throw(": Negative number detected!");
			}
			vectorContainer.push_back(currentNumber);
			dequeContainer.push_back(currentNumber);
		}


		// Print initial state
		merger.printVector(vectorContainer, true);
		merger.printDeque(dequeContainer, true);

		// Calculate sorting time for vector
		std::clock_t start = std::clock();
		merger.fordJohnsonVector(vectorContainer, 0, vectorContainer.size() - 1);
		std::clock_t end = std::clock();
		elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
		vectorSortingTime = elapsed;

		// Calculate sorting time for deque
		start = std::clock();
		merger.fordJohnsonDeque(dequeContainer, 0, dequeContainer.size() - 1);
		end = std::clock();
		elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
		dequeSortingTime = elapsed;

		// Print sorted state and sorting times
		merger.printVector(vectorContainer, false);
		merger.printDeque(dequeContainer, false);
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << vectorSortingTime << " us" << std::endl;
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque :  " << dequeSortingTime << " us" << std::endl;
	}
	catch (const char *errorMsg)
	{
		std::cout << "Error " << errorMsg << std::endl;
	}
	return 0;
}
