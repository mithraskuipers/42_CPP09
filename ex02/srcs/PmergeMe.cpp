/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/20 17:43:27 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

// *****************************************************************************
// Program wrapper
// *****************************************************************************

void PmergeMe::wrapper(std::vector<int> &Vcontainer, std::deque<int> &Dcontainer, uint &vecTime, uint &deqTime)
{
    std::clock_t start = std::clock();
    fordJohnsonVector(Vcontainer, 0, Vcontainer.size() - 1);
    std::clock_t end = std::clock();
    double elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
    vecTime = elapsed;
    
    start = std::clock();
    fordJohnsonDeque(Dcontainer, 0, Dcontainer.size() - 1);
    end = std::clock();
    elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
    deqTime = elapsed;
}


// *****************************************************************************
// Vector
// *****************************************************************************

void PmergeMe::fordJohnsonVector(std::vector<int> &container, int start, int end)
{
	int newEnd;
	if (start < end)
	{
		if ((end - start) < 10)
		{
			insertSortVector(container, start, end);
		}
		else
		{
			newEnd = start + (end - start) / 2;
			fordJohnsonVector(container, start, newEnd);
			fordJohnsonVector(container, START(newEnd), end);
			mergeSortVector(container, start, newEnd, end);
		}
	}
}

void PmergeMe::mergeSortVector(std::vector<int> &container, int start, int mid, int end)
{
	int i, j, k;

	std::vector<int> left(mid - start + 1);
	std::vector<int> right(end - mid);

	for (i = 0; i < (mid - start + 1); ++i)
	{
		left[i] = container[start + i];
	}
	for (j = 0; j < (end - mid); ++j)
	{
		right[j] = container[mid + 1 + j];
	}
	i = 0;
	j = 0;
	k = start;
	while (i < (mid - start + 1) && j < (end - mid))
	{
		if (left[i] <= right[j])
		{
			container[k] = left[i];
			k++;
			i++;
		}
		else
		{
			container[k] = right[j];
			k++;
			j++;
		}
	}

	while (i < (mid - start + 1))
	{
		container[k] = left[i];
		k++;
		i++;
	}
	while (j < (end - mid))
	{
		container[k] = right[j];
		k++;
		j++;
	}
}

void PmergeMe::insertSortVector(std::vector<int> &container, int start, int end)
{
	int n = end - start + 1; // Number of elements to sort

	for (int i = 1; i < n; i++)
	{
		int key = container[start + i];
		int j = i - 1;

		// Find position to insert based on Jacobsthal numbers
		while (j >= 0 && container[start + j] > key)
		{
			// Adjust the condition to consider Jacobsthal numbers
			if (j >= 0 && j == jacobsthal(i) - 2)
			{
				container[start + j + 1] = container[start + j]; // Shift element to the right
				j--;											 // Decrement j again for correct placement
			}
			container[start + j + 1] = container[start + j]; // Shift element to the right
			j--;
		}
		container[start + j + 1] = key; // Insert key in the correct position
	}
}

void PmergeMe::insertSortDeque(std::deque<int> &container, int start, int end)
{
	int n = end - start + 1; // Number of elements to sort

	for (int i = 1; i < n; i++)
	{
		int key = container[start + i];
		int j = i - 1;

		// Find position to insert based on Jacobsthal numbers
		while (j >= 0 && container[start + j] > key)
		{
			// Adjust the condition to consider Jacobsthal numbers
			if (j >= 0 && j == jacobsthal(i) - 2)
			{
				container[start + j + 1] = container[start + j]; // Shift element to the right
				j--;											 // Decrement j again for correct placement
			}
			container[start + j + 1] = container[start + j]; // Shift element to the right
			j--;
		}
		container[start + j + 1] = key; // Insert key in the correct position
	}
}

// *****************************************************************************
// Deque
// *****************************************************************************

void PmergeMe::fordJohnsonDeque(std::deque<int> &container, int start, int end)
{
	int newEnd;
	if (start < end)
	{
		if ((end - start) < 10)
			insertSortDeque(container, start, end);
		else
		{
			newEnd = start + (end - start) / 2;
			fordJohnsonDeque(container, start, newEnd);
			fordJohnsonDeque(container, START(newEnd), end);
			mergeSortDeque(container, start, newEnd, end);
		}
	}
}

void PmergeMe::mergeSortDeque(std::deque<int> &container, int start, int mid, int end)
{
	int i;
	int j;
	int k;

	std::deque<int> left(mid - start + 1);
	std::deque<int> right(end - mid);

	for (i = 0; i < (mid - start + 1); ++i)
	{
		left[i] = container[start + i];
	}
	for (j = 0; j < (end - mid); ++j)
	{
		right[j] = container[mid + 1 + j];
	}
	i = 0;
	j = 0;
	k = start;
	while (i < (mid - start + 1) && j < (end - mid))
	{
		if (left[i] <= right[j])
		{
			container[k] = left[i];
			k++;
			i++;
		}
		else
		{
			container[k] = right[j];
			k++;
			j++;
		}
	}

	while (i < (mid - start + 1))
	{
		container[k] = left[i];
		k++;
		i++;
	}
	while (j < (end - mid))
	{
		container[k] = right[j];
		k++;
		j++;
	}
}

// *****************************************************************************
// Misc
// *****************************************************************************

// Calculate Jacobsthal number
int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void PmergeMe::printVector(const std::vector<int> &vectorContainer, bool isBefore) {
    if (isBefore) {
        std::cout << "Vector before sorting: ";
    } else {
        std::cout << "Vector after sorting: ";
    }
    for (const auto &element : vectorContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printDeque(const std::deque<int> &dequeContainer, bool isBefore) {
    if (isBefore) {
        std::cout << "Deque before sorting: ";
    } else {
        std::cout << "Deque after sorting: ";
    }
    for (const auto &element : dequeContainer) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


// Commented out operator = overload since there is nothing to copy over.
// PmergeMe &PmergeMe::operator=(const PmergeMe &other)
// {
// 	if (this == &other)
// 	{
// 		return (*this);
// 	}
// 	return (*this);
// }

// Commented out custom copy constructor since there is nothing to copy over.
// PmergeMe::PmergeMe(const PmergeMe &other)
// {
// 	(void)(other);
// }
