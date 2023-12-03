/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/17 13:24:56 by mikuiper      ########   odam.nl         */
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
	clock_t start = clock();													// Record the start time
	this->fordJohnsonSort(this->intVector, 0, this->intVector.size() - 1);		// Size of vector: this->intVector.size()
	clock_t stop = clock();														// Record the stop time
	std::cout << "After: ";
	this->intVectorPrinter();
	double duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000;		// Calculate the duration in microseconds
	std::cout << "Time to process a range of " << this->intVector.size() << " elements with std::vector : " << duration << " us" << std::endl;

	/* integer deque */
	std::cout << "Before: ";
	this->intDequePrinter();
	start = clock();															// Record the start time
	this->fordJohnsonSort(this->intDeque, 0, this->intDeque.size() - 1);		// Size of deque: this->intDeque.size()
	stop = clock();																// Record the stop time
	std::cout << "After: ";
	this->intDequePrinter();
	duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000;				// Calculate the duration in microseconds
	std::cout << "Time to process a range of " << this->intDeque.size() << " elements with std::deque : " << duration << " us" << std::endl;
}

/*
Source:
https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort
*/

/*
Algorithm workings:
It receives a list of elements.

*/

template<typename T>
void PmergeMe::mergeSublists(T &lst, int lst_start_idx, int mid, int lst_end_idx)
{
	int left_idx = lst_start_idx;												// Index of the current left sublist of interest. Changes with each iteration.
	int right_index = mid + 1;													// Start of the current right sublist interest. Changes with each iteration.
	int temp_index = 0;														// Index for merging the sublists.
	std::vector<int> temp(lst_end_idx - lst_start_idx + 1);						// Vector to store merged elements.

	while ((left_idx <= mid) && (right_index <= lst_end_idx))					// Merge elements from left and right sublists into the temporary vector
	{
		if (lst[left_idx] <= lst[right_index])									// Compare elements from left and right sublists, and merge them in ascending order
		{
			temp[temp_index] = lst[left_idx];									// Merge element from the left sublist
			temp_index++;
			left_idx++;
		}
		else
		{
			temp[temp_index] = lst[right_index];								// Merge element from the right sublist
			temp_index++;
			right_index++;
		}
	}

	while (left_idx <= mid)														// Copy any remaining elements from the left sublist to the temporary vector
	{
		temp[temp_index++] = lst[left_idx++];
	}

	while (right_index <= lst_end_idx)											// Copy any remaining elements from the right sublist to the temporary vector
	{
		temp[temp_index++] = lst[right_index++];
	}

	for (int p = 0; p < temp_index; p++)										// Copy the merged elements back to the original list starting from lst_start_idx
	{
		lst[lst_start_idx + p] = temp[p];
	}
}

template<typename T>
void PmergeMe::fordJohnsonSort(T &lst, int lst_start_idx, int lst_end_idx)
{
	int lst_mid_idx;

	if (lst_start_idx != lst_end_idx)											// If the sublist has more than one item, continue dividing it
	{
		// Further splitting in left sublist and right sublists..

		lst_mid_idx = lst_start_idx + ((lst_end_idx - lst_start_idx) / 2);			// Find the middle index of the sublist

		// Left sublist
		fordJohnsonSort(lst, lst_start_idx, lst_mid_idx);								// Recursively sort the left half of the sublist

		// Right sublist
		fordJohnsonSort(lst, lst_mid_idx + 1, lst_end_idx);								// Recursively sort the right half of the sublist

		mergeSublists(lst, lst_start_idx, lst_mid_idx, lst_end_idx);					// Merge the sorted halves back together
	}
}

// Explicitly instantiate the template for specific types
template void PmergeMe::fordJohnsonSort(std::vector<int> &lst, int lst_start_idx, int lst_end_idx);
template void PmergeMe::fordJohnsonSort(std::deque<int> &lst, int lst_start_idx, int lst_end_idx);


/*
mergeSublists is called multiple times during the merge sort process. Let me provide a more detailed explanation, including the second call to mergeSublists in step 5.

    Initial Call: fordJohnsonSort([1, 3, 5, 2, 4], 0, 4)
        Divides the list into two sublists: [1, 3] and [5, 2, 4]
        Calls fordJohnsonSort([1, 3], 0, 1) and fordJohnsonSort([5, 2, 4], 2, 4)

    Left Sublist [1, 3] (sublist indices 0 to 1):
        Already sorted; no further recursive calls or merges needed.

    Right Sublist [5, 2, 4] (sublist indices 2 to 4):
        Divides into two sublists: [5] and [2, 4]
        Calls fordJohnsonSort([5], 2, 2) and fordJohnsonSort([2, 4], 3, 4)

    Sublist [5] (sublist index 2):
        Already sorted; no further recursive calls or merges needed.

    Sublist [2, 4] (sublist indices 3 to 4):
        Divides into individual elements, which are already sorted.

    Merging Step 1: mergeSublists([2, 4], 3, 4)
        Merging the sorted sublists [2] and [4] into [2, 4].
        Resulting sublist: [2, 4]

    Merging Step 2: mergeSublists([5], 2, 2) and mergeSublists([2, 4], 3, 4)
        Merging the sorted sublists [5] and [2, 4] into a single sorted sublist.
        Resulting sublist: [2, 4, 5]

    Final Merge: mergeSublists([1, 3], 0, 1) and mergeSublists([2, 4, 5], 2, 4)
        Merging the sorted sublists [1, 3] and [2, 4, 5] into a single sorted list.
        Resulting sorted list: [1, 2, 3, 4, 5]

In this explanation, mergeSublists is indeed called twice during the merging process. The second call occurs when merging the sorted sublists [5] and [2, 4] into a single sorted sublist. This results in the final sorted list [1, 2, 3, 4, 5].
User
I have a question about step 8
Wouldnt merging [1,3] and [2,4,5] result in [1,3,2,4,5] ?
ChatGPT

I see where the confusion might arise. In the merge step between [1, 3] and [2, 4, 5], the comparison between elements ensures that the sorting order is maintained. Let me break down the process more explicitly for step 8:

    Sublist [1, 3] (indices 0 to 1) and Sublist [2, 4, 5] (indices 2 to 4):
        Compare the first elements of both sublists: 1 and 2.
            Since 1 is smaller, it comes first in the merged list: [1].
            Move to the next element in the [1, 3] sublist.
        Compare the next elements: 3 and 2.
            Since 2 is smaller, it comes next in the merged list: [1, 2].
            Move to the next element in the [2, 4, 5] sublist.
        Compare the next elements: 3 and 4.
            Since 3 is smaller, it comes next in the merged list: [1, 2, 3].
            Move to the next element in the [1, 3] sublist.
        The [1, 3] sublist is now empty. Add the remaining elements from the [2, 4, 5] sublist to the merged list.
            Merged list: [1, 2, 3, 4, 5].

By comparing and merging the elements in the correct order, the merged list becomes [1, 2, 3, 4, 5], which is the sorted result of merging [1, 3] and [2, 4, 5].
*/