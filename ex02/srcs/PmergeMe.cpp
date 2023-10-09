/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/09 12:58:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	
}

PmergeMe::~PmergeMe()
{
	
}

// Copy Constructor
PmergeMe::PmergeMe(const PmergeMe &other)
{
	// Copy elements from the other object's intVector and intDeque to this object
	this->intVector = other.intVector;
	this->intDeque = other.intDeque;
}

// Assignment Operator Overload
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	// Check for self-assignment
	if (this != &other)
	{
		// Copy elements from the other object's intVector and intDeque to this object
		this->intVector = other.intVector;
		this->intDeque = other.intDeque;
	}
	// Return the reference to this object to enable chained assignments (e.g., a = b = c)
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
	for (int left_idx = 1; argv[left_idx]; left_idx++)
	{
		this->intVector.push_back(std::atoi(argv[left_idx]));
		this->intDeque.push_back(std::atoi(argv[left_idx]));
	}
}

void PmergeMe::fordJohnsonSortWrapper()
{
	/* integer vector */
	std::cout << "Before: ";
	this->intVectorPrinter();
	clock_t start = clock(); // Record the start time
	this->fordJohnsonSort(this->intVector, 0, this->intVector.size() - 1);
	clock_t stop = clock(); // Record the stop time
	std::cout << "After: ";
	this->intVectorPrinter();
	double duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000; // Calculate the duration in microseconds
	std::cout << "Time taken by function: " << duration << " microseconds" << std::endl;

	/* integer deque */
	// /*
	std::cout << "Before: ";
	this->intDequePrinter();
	start = clock(); // Record the start time
	this->fordJohnsonSort(this->intDeque, 0, this->intDeque.size() - 1);
	stop = clock(); // Record the stop time
	std::cout << "After: ";
	this->intDequePrinter();
	duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000; // Calculate the duration in microseconds
	std::cout << "Time taken by function: " << duration << " microseconds" << std::endl;
	// */


}

template<typename T>
void PmergeMe::mergeSublists(T &lst, int lst_start_idx, int mid, int lst_end_idx)
{
	// Initialize variables for left and right sublist indices, merged elements index, and temporary vector
	int left_idx = lst_start_idx;												// Index of the left sublist
	int right_index = mid + 1;													// Index of the right sublist
	int merged_index = 0;														// Index for the merged elements in the temporary vector
	std::vector<int> temp(lst_end_idx - lst_start_idx + 1);						// Temporary vector to store merged elements

	while ((left_idx <= mid) && (right_index <= lst_end_idx))					// Merge elements from left and right sublists into the temporary vector
	{
		if (lst[left_idx] <= lst[right_index])									// Compare elements from left and right sublists, and merge them in ascending order
		{
			temp[merged_index++] = lst[left_idx++];								// Merge element from the left sublist
		}
		else
		{
			temp[merged_index++] = lst[right_index++];							// Merge element from the right sublist
		}
	}

	while (left_idx <= mid)														// Copy any remaining elements from the left sublist to the temporary vector
	{
		temp[merged_index++] = lst[left_idx++];
	}

	while (right_index <= lst_end_idx)											// Copy any remaining elements from the right sublist to the temporary vector
	{
		temp[merged_index++] = lst[right_index++];
	}

	for (int p = 0; p < merged_index; p++)										// Copy the merged elements back to the original list starting from lst_start_idx
	{
		lst[lst_start_idx + p] = temp[p];
	}
}

template<typename T>
void PmergeMe::fordJohnsonSort(T &lst, int lst_start_idx, int lst_end_idx)
{
	if (lst_start_idx < lst_end_idx)											// If the sublist has more than one item, continue dividing it
	{
		int mid = lst_start_idx + ((lst_end_idx - lst_start_idx) / 2);			// Find the middle index of the sublist

		fordJohnsonSort(lst, lst_start_idx, mid);								// Recursively sort the left half of the sublist

		fordJohnsonSort(lst, mid + 1, lst_end_idx);								// Recursively sort the right half of the sublist

		mergeSublists(lst, lst_start_idx, mid, lst_end_idx);					// Merge the sorted halves back together
	}
}

// Explicitly instantiate the template for specific types
template void PmergeMe::fordJohnsonSort(std::vector<int> &lst, int lst_start_idx, int lst_end_idx);
template void PmergeMe::fordJohnsonSort(std::deque<int> &lst, int lst_start_idx, int lst_end_idx);