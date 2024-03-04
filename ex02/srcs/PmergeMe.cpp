/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/23 21:06:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

/*
** WRAPPER
*/

// Wrapper function to execute the sorting algorithms and measure time
void PmergeMe::wrapper(std::vector<int> &Vcontainer, std::deque<int> &Dcontainer, uint &vecTime, uint &deqTime)
{
	PmergeMe merger; // Create an instance of the PmergeMe class

	// VECTOR
	std::clock_t start = std::clock();
	if (Vcontainer.size() % 2 != 0)
	{
		merger.handleOddElements(Vcontainer);
	}
	recursiveSortingVector(Vcontainer, 0, Vcontainer.size() - 1);
	std::clock_t end = std::clock();
	double elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
	vecTime = elapsed;

	// DEQUE
	start = std::clock();
	if (Dcontainer.size() % 2 != 0)
	{
		merger.handleOddElements(Dcontainer);
	}
	recursiveSortingDeque(Dcontainer, 0, Dcontainer.size() - 1);
	end = std::clock();
	elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
	deqTime = elapsed;
}

/*
** STEP 1
*/

// Step 1: Pairwise sorting - Vector
// Pairwise sorting for a vector
void PmergeMe::pairwiseSortVector(std::vector<int> &container)
{

	for (size_t i = 0; i < container.size() - 1; i += 2)
	{
		if (container[i] > container[i + 1])
		{
			std::swap(container[i], container[i + 1]); // Swap elements if out of order
		}
	}
}

// Step 1: Pairwise sorting - Deque
// Pairwise sorting for a deque
void PmergeMe::pairwiseSortDeque(std::deque<int> &container)
{

	for (size_t i = 0; i < container.size() - 1; i += 2)
	{
		if (container[i] > container[i + 1])
		{
			std::swap(container[i], container[i + 1]); // Swap elements if out of order
		}
	}
}

// Step 1: Handling odd elements - Vector
// Handle odd elements in a vector
void PmergeMe::handleOddElements(std::vector<int> &container)
{
	int lastElement = container.back(); // Get the last element
	container.pop_back(); // Remove the last element
	insertSortVector(container, 0, container.size() - 1); // Sort the vector
	container.push_back(lastElement); // Put back the last element
}

// Step 1: Handling odd elements - Deque
// Handle odd elements in a deque
void PmergeMe::handleOddElements(std::deque<int> &container)
{
	int lastElement = container.back(); // Get the last element
	container.pop_back(); // Remove the last element
	insertSortDeque(container, 0, container.size() - 1); // Sort the deque
	container.push_back(lastElement); // Put back the last element
}

/*
** STEP 2
*/

// Step 2: Recursive sorting - Vector
// Ford-Johnson algorithm for vector
void PmergeMe::recursiveSortingVector(std::vector<int> &container, int start, int end)
{
	if (start < end) // splitting until individual elements are reached. If clause happens if there is more than 1.
	{
		int midpoint = start + (end - start) / 2;
		recursiveSortingVector(container, start, midpoint); // Recursively sort left half
		recursiveSortingVector(container, midpoint + 1, end); // Recursively sort right half
		mergeSortedHalvesVector(container, start, midpoint, end); // Merge the sorted halves
		insertPendVector(container, start, midpoint, end); // Insert pend elements
	}
}

// Step 2: Recursive sorting - Deque
// Ford-Johnson algorithm for deque
void PmergeMe::recursiveSortingDeque(std::deque<int> &container, int start, int end)
{
	if (start < end) // splitting until individual elements are reached. If clause happens if there is more than 1.
	{
		int midpoint = start + (end - start) / 2;
		recursiveSortingDeque(container, start, midpoint); // Recursively sort left half
		recursiveSortingDeque(container, midpoint + 1, end); // Recursively sort right half
		mergeSortedHalvesDeque(container, start, midpoint, end); // Merge the sorted halves
		insertPendDeque(container, start, midpoint, end); // Insert pend elements
	}
}

/*
-> recursiveSortingDeque(): Recursion Depth:
The recursion continues until individual elements are reached, splitting the deque into smaller halves:
At depth 0: [5, 4, 3, 2, 1]
At depth 1: [5, 4, 3] and [2, 1]
At depth 2: [5, 4], [3], [2], [1]

-> mergeSortedHalvesDeque(): Merge Sorted Halves:
When recursion has reached the end, mergeSortedHalvesDeque() starts merging the sorted halves:
- Merge [5, 4] and [3] to get [3, 4, 5]:
  - Compare elements 5 and 3, place 3 first, then compare 5 and 4, place 4 next, and finally place 5.
- Merge [2] and [1] to get [1, 2]:
  - Since it's only one element each, no comparison is needed.
At depth 1: [3, 4, 5] and [1, 2]

The merging process ensures that within each pair of sorted halves, the elements are rearranged such that the resulting merged sequence is sorted in ascending order.

-> insertPendDeque(): Final Merge and Insert Pend Elements:

At depth 0, merge [3, 4, 5] and [1, 2] to get the final sorted deque: [1, 2, 3, 4, 5].

1. Initialize two pointers, one for each sorted half: leftPtr for [3, 4, 5] and rightPtr for [1, 2].
2. Determine the insertion points using Jacobsthal numbers:
    - For the first element from the pending deque, which is 1, we use the second Jacobsthal number, which is 1. This means we insert the first element at index 1 in the main chain.
    - For the second element from the pending deque, which is 2, we use the third Jacobsthal number. In this case, the third Jacobsthal number is also 1, indicating that we again insert the second element at index 1 in the main chain.
3. Compare elements pointed to by leftPtr and rightPtr.
4. If the element pointed to by leftPtr is smaller or equal to the element pointed to by rightPtr, copy the element from the left half to the final deque and move leftPtr to the next element.
5. If the element pointed to by rightPtr is smaller, copy it to the final deque and move rightPtr to the next element.
6. Repeat steps 3-5 until all elements from both halves are merged into the final deque.
*/

/*
** STEP 3
*/

// Step 3: Merge sort - [Vector]
// Merge sort for vector
void PmergeMe::mergeSortedHalvesVector(std::vector<int> &container, int start, int mid, int end)
{
	int i;
	int j;
	int k;

	std::vector<int> left(mid - start + 1);
	std::vector<int> right(end - mid);

	for (i = 0; i < (mid - start + 1); i++)
	{
		left[i] = container[start + i];
	}
	for (j = 0; j < (end - mid); j++)
	{
		right[j] = container[mid + 1 + j];
	}
	i = 0;
	j = 0;
	k = start;
	// Merge the two sorted halves of the container into a single sorted sequence
	while (i < (mid - start + 1) && j < (end - mid))
	{
		// Compare elements from the left/right halves and merge in container
		if (left[i] <= right[j])
		{
			// If the element in the left half is smaller or equal, copy it to the container
			container[k] = left[i];
			k++; // Move to the next position in the container
			i++; // Move to the next element in the left half
		}
		else
		{
			// If the element in the right half is smaller, copy it to the container
			container[k] = right[j];
			k++; // Move to the next position in the container
			j++; // Move to the next element in the right half
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

// Step 3: Merge sort - [Deque]
// Merge sort for deque
void PmergeMe::mergeSortedHalvesDeque(std::deque<int> &container, int start, int mid, int end)
{
	int i;
	int j;
	int k;

	std::deque<int> left(mid - start + 1);
	std::deque<int> right(end - mid);

	for (i = 0; i < (mid - start + 1); i++)
	{
		left[i] = container[start + i];
	}
	for (j = 0; j < (end - mid); j++)
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

// Step 3: Insert pend elements - [Vector]
// Insertion sort for vector
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
			if (j >= 0 && j == jacobsthal(i) - 2)
			{
				container[start + j + 1] = container[start + j];
				j--;
			}
			container[start + j + 1] = container[start + j];
			j--;
		}
		container[start + j + 1] = key;
	}
}

// Step 3: Insert pend elements - [Deque]
// Insertion sort for deque
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
			if (j >= 0 && j == jacobsthal(i) - 2)
			{
				container[start + j + 1] = container[start + j];
				j--;
			}
			container[start + j + 1] = container[start + j];
			j--;
		}
		container[start + j + 1] = key;
	}
}

/*
Insertion sort example:

Initial Array: [5, 4, 3, 2, 1]
[5, 4, 3, 2, 1]
Compare 4 with 5
[4, 5, 3, 2, 1]
Compare 3 with 5
[4, 3, 5, 2, 1]
Compare 3 with 4
[3, 4, 5, 2, 1]
Compare 2 with 5
[3, 4, 2, 5, 1]
Compare 2 with 4
[3, 2, 4, 5, 1]
Compare 2 with 3
[2, 3, 4, 5, 1]
Compare 1 with 5
[2, 3, 4, 1, 5]
Compare 1 with 4
[2, 3, 1, 4, 5]
Compare 1 with 3
[2, 1, 3, 4, 5]
Compare 1 with 2
[1, 2, 3, 4, 5]
*/



// Step 3: Insert pend elements - [Vector]
// Insert pend elements into the sorted main chain for vector
void PmergeMe::insertPendVector(std::vector<int> &container, int start, int mid, int end)
{
    // Create a temporary vector to hold pend elements
    std::vector<int> pendElements;

    // Traverse the sorted main chain to find pend positions
    size_t i = start;
    size_t j = mid + 1;
    int jacobsthalIndex = 0; // Initialize Jacobsthal number index

    while (i <= static_cast<size_t>(mid) && j <= static_cast<size_t>(end))
    {
        if (jacobsthalIndex == 0)
        {
            pendElements.push_back(container[i]);
            i++;
        }
        else if (i == start + static_cast<size_t>(jacobsthal(jacobsthalIndex)) - 1)
        {
            pendElements.push_back(container[j]);
            j++;
            jacobsthalIndex++;
        }
        else
        {
            pendElements.push_back(container[i]);
            i++;
        }
		printPendElementsVector(pendElements);
    }

    // Insert pend elements into the sorted main chain
    size_t pendIndex = start;
    for (int pendElement : pendElements)
    {
        container[pendIndex] = pendElement;
        pendIndex++;
    }
}

void PmergeMe::insertPendDeque(std::deque<int> &container, int start, int mid, int end)
{
    std::deque<int> pendElements;

    size_t i = start;
    size_t j = mid + 1;
    int jacobsthalIndex = 0;

    while (i <= static_cast<size_t>(mid) && j <= static_cast<size_t>(end))
    {
        if (jacobsthalIndex == 0)
        {
            pendElements.push_back(container[i]);
            i++;
        }
		else if (i == start + static_cast<size_t>(jacobsthal(jacobsthalIndex)) - 1)
        {
            pendElements.push_back(container[j]);
            j++;
            jacobsthalIndex++;
        }
        else
        {
            pendElements.push_back(container[i]);
            i++;
        }
    }

    while (i <= static_cast<size_t>(mid))
    {
        pendElements.push_back(container[i]);
        i++;
    }

    while (j <= static_cast<size_t>(end))
    {
        pendElements.push_back(container[j]);
        j++;
    }

    size_t pendIndex = start;
    for (int pendElement : pendElements)
    {
        container[pendIndex] = pendElement;
        pendIndex++;
    }
}

/*
The "Pend Elements" lines represent the elements that are identified as pending during the sorting process. These elements are temporarily held aside until they can be inserted into the sorted main chain based on their positions determined by the Jacobsthal numbers.
Let's analyze why the Pend Elements lines make sense in the order they are shown for the specific input "5 4 3 2 1 99 0":
Pend Elements (Vector): 4: During the sorting process, the algorithm identifies that 4 needs to be placed at index 1 based on the Jacobsthal sequence.
Pend Elements (Vector): 2: Similarly, 2 needs to be placed at index 1.
Pend Elements (Vector): 2: Here, we have another 2, which is placed at index 1 again, indicating that there are multiple elements with the same value that need to be inserted at the same position in the sorted chain.
Pend Elements (Vector): 2 3: Now, the algorithm identifies that 3 should be placed at index 2.
Pend Elements (Vector): 1: The algorithm finds that 1 needs to be placed at index 1.
Pend Elements (Vector): 0: 0 is identified to be placed at index 0.
Pend Elements (Vector): 0 1: Here, both 0 and 1 are inserted at their respective positions.
Pend Elements (Vector): 0: Another 0 is identified and placed at index 0.
Pend Elements (Vector): 0 1: Again, 0 and 1 are inserted at their respective positions.
Pend Elements (Vector): 0 1 2: The algorithm identifies that 2 should be placed at index 2.
Pend Elements (Vector): 0 1 2 3: Finally, 3 is placed at index 3, completing the sorting process.
Each line in the "Pend Elements" output corresponds to an iteration of identifying and inserting pending elements into the sorted main chain. The order of these lines reflects the positions where elements need to be inserted based on the Jacobsthal sequence, ensuring that the final sorted sequence is correct.
*/

// Compute the n-th Jacobsthal number
int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

/*
Definition Jacobsthal numbers
Jacobsthal(0) = 0
Jacobsthal(1) = 1
Jacobsthal(n) = Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2) for n >= 2

Jacobsthal numbers help determine the positions for inserting these pending elements.
*/

// PRINTING
void PmergeMe::printVector(const std::vector<int> &vectorContainer, bool isBefore)
{
    // Print the vector container

	if (isBefore)
	{
		std::cout << "Vector before sorting: ";
	}
	else
	{
		std::cout << "Vector after sorting: ";
	}
	for (const auto &element : vectorContainer)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printDeque(const std::deque<int> &dequeContainer, bool isBefore)
{
    // Print the deque container

	if (isBefore)
	{
		std::cout << "Deque before sorting: ";
	}
	else
	{
		std::cout << "Deque after sorting: ";
	}
	for (const auto &element : dequeContainer)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

// For debugging. Function to print the contents of the pendElements container for vector
void PmergeMe::printPendElementsVector(const std::vector<int> &pendElements)
{
    std::cout << "Pend Elements (Vector): ";
    for (int element : pendElements)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// For debugging Function to print the contents of the pendElements container for deque
void PmergeMe::printPendElementsDeque(const std::deque<int> &pendElements)
{
    std::cout << "Pend Elements (Deque): ";
    for (int element : pendElements)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

/*
Algorithm code implementation overview:
Pairwise Sorting (Step 1):
This step involves sorting adjacent pairs of elements within the container.
If an element is greater than its adjacent element, 
they are swapped to ensure that the sequence is sorted pairwise.

Handling Odd Elements (Step 1):
If the container has an odd number of elements,
the last element is temporarily removed, and the remaining elements are sorted using the pairwise sorting algorithm.
Once sorted, the last element is inserted back into the container.

Recursive Sorting (Step 2):
The container is recursively split into halves until individual elements are reached.
For each recursive call, the left and right halves of the container are sorted independently.
After sorting, the sorted halves are merged together.

Merging Sorted Halves (Step 3):
This step involves merging two sorted halves of the container into a single sorted sequence.
The algorithm compares elements from the left and right halves and merges them into the final sorted sequence.

Insert Pend Elements (Step 3):
After merging the sorted halves, pending elements are inserted into the sorted main chain based on Jacobsthal numbers.
Jacobsthal numbers determine the positions for inserting these pending elements into the sorted sequence.
The algorithm iterates over the sorted main chain and inserts pending elements at the calculated positions.

Jacobsthal Numbers:
Jacobsthal numbers are computed recursively using the formula:
Jacobsthal(n) = Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2).
These numbers are used to determine the positions for inserting pending elements during the merge sort process.
The jacobsthal() function computes the n-th Jacobsthal number.

Printing Functions:
The provided code includes functions to print the contents of the vector and deque containers before and after sorting,
as well as functions to print the pending elements for debugging purposes.
*/