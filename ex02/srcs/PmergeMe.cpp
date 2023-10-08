/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/08 21:31:49 by mikuiper      ########   odam.nl         */
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


void PmergeMe::readInput(char **argv)
{
	for (int i = 1; argv[i]; i++)
	{
		this->intVector.push_back(std::atoi(argv[i]));
		this->intDeque.push_back(std::atoi(argv[i]));
	}
}

void PmergeMe::fordJohnsonSortWrapper()
{
	/* integer vector */
	std::cout << "Before: ";
	this->intVectorPrinter();
	
	this->fordJohnsonSort(this->intVector, 0, this->intVector.size() - 1);

	std::cout << "After: ";
	this->intVectorPrinter();

	/* integer deque */
	/*
	std::cout << "Before: ";
	this->intDequePrinter();
	
	this->fordJohnsonSort(this->intDeque, 0, this->intDeque.size() - 1);

	std::cout << "After: ";
	this->intDequePrinter();
	*/
}

template<typename T>
void PmergeMe::fordJohnsonSort(T &lst, int beg, int end)						// Uses iterators, no assumptions about container type
{
	// Base case: if the sublist has one or zero elements, it is already sorted
	if (beg < end)
	{
		// Find the middle index of the sublist
		int mid = beg + (end - beg) / 2;
		
		// Recursively sort the left half of the sublist
		fordJohnsonSort(lst, beg, mid);
		
		// Recursively sort the right half of the sublist
		fordJohnsonSort(lst, mid + 1, end);

		// Merge the sorted halves
		
		// Temporary vector to store the merged elements
		std::vector<int> temp(end - beg + 1);
		int i = beg, j = mid + 1, k = 0;

		// Compare elements from the left and right halves and merge them into temp vector
		while (i <= mid && j <= end)
		{
			if (lst[i] <= lst[j]) {
				temp[k++] = lst[i++];
			} else {
				temp[k++] = lst[j++];
			}
		}

		// If there are remaining elements in the left half, copy them to temp vector
		while (i <= mid)
		{
			temp[k++] = lst[i++];
		}

		// If there are remaining elements in the right half, copy them to temp vector
		while (j <= end)
		{
			temp[k++] = lst[j++];
		}

		// Copy the merged elements back to the original list
		for (int p = 0; p < k; p++)
		{
			lst[beg + p] = temp[p];
		}
	}
}


// Explicitly instantiate the template for specific types
template void PmergeMe::fordJohnsonSort(std::vector<int> &lst, int beg, int end);
template void PmergeMe::fordJohnsonSort(std::deque<int> &lst, int beg, int end);