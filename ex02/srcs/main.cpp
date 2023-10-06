/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/06 18:35:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int isPositiveNumber(const std::string &s)
{
	if (s.empty())
	{
		return (0);
	}
	for (std::size_t i = 0; i < s.length(); i++)
	{
		if (!std::isdigit(s[i]))
		{
			return (0);
		}
	}
	return (1);
}

int isInputValid(char **argv)
{
	for (int i = 1; argv[i]; i++)
	{
		if (!isPositiveNumber(argv[i]))
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


	PmergeMe	mergeMe;
	mergeMe.fordJohnsonSort(argv);
	

	return (0);
}


/*
make re && ./PmergeMe 3 5 9 7 4 ;
make re && ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "` ;
*/