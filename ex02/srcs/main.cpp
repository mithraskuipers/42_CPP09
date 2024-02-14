/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/14 12:39:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
NOTE: THIS CPP09 EX02 IMPLEMENTATION USES:
(1) std::vector<int>
(2) std::deque<int>
*/

/*
make re ; ./PmergeMe $(shuf -i 10-100 -n 30) ;
make re ; ./PmergeMe $(shuf -i 1-100000 -n 3000) ;

For explanations:
make re ; ./PmergeMe 4 1 3 2 ;
*/

int isPositiveNumber(const std::string &s)
{
	if (s.empty())
	{
		return (0);
	}
	for (std::size_t left_idx = 0; left_idx < s.length(); left_idx++)
	{
		if (!std::isdigit(s[left_idx]))
		{
			return (0);
		}
	}
	return (1);
}

int isInputValid(char **argv)
{
	for (int left_idx = 1; argv[left_idx]; left_idx++)
	{
		if (!isPositiveNumber(argv[left_idx]))
		{
			return (0);
		}
	}
	return (1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: ./PmergeMe <positive_number_sequence>" << std::endl;
		return 1;
	}

	if (!isInputValid(argv))
	{
		std::cout << "Error: Invalid input" << std::endl;
		return 1;
	}

	PmergeMe mergeMe;
	mergeMe.readInput(argv);
	mergeMe.setPrintOutput(0);
	mergeMe.fordJohnsonSortWrapper();

	return (0);
}
