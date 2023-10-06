/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/06 18:44:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	
}

PmergeMe::~PmergeMe()
{
	
}

// TODO
PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

// TODO
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	this->intVector = other.intVector;
	this->intDeque = other.intDeque;

	return (*this);
}

void	PmergeMe::intVectorPrinter()
{
	for (std::vector<int>::iterator it = intVector.begin(); it != intVector.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	return ;
}


void	PmergeMe::intDequePrinter()
{
	for (std::deque<int>::iterator it = intDeque.begin(); it != intDeque.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	return ;
}


void PmergeMe::fordJohnsonSort(char **argv)
{
	for (int i = 1; argv[i]; i++)
	{
		intVector.push_back(std::atoi(argv[i]));
		intDeque.push_back(std::atoi(argv[i]));
	}
	std::cout << "Before: ";
	intVectorPrinter();
	
	std::cout << "Before: ";
	intDequePrinter();
}