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
	fordJohnsonVector(Vcontainer, 0, Vcontainer.size() - 1);
	std::clock_t end = std::clock();
	double elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
	vecTime = elapsed;

	// DEQUE
	start = std::clock();
	if (Dcontainer.size() % 2 != 0)
	{
		merger.handleOddElements(Dcontainer);
	}
	fordJohnsonDeque(Dcontainer, 0, Dcontainer.size() - 1);
	end = std::clock();
	elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
	deqTime = elapsed;
}

/*
** STEP 1
*/

void PmergeMe::pairwiseSortVector(std::vector<int> &container)
{
    // Step 1: Pairwise sorting - Vector
	// Pairwise sorting for a vector
	for (size_t i = 0; i < container.size() - 1; i += 2)
	{
		if (container[i] > container[i + 1])
		{
			std::swap(container[i], container[i + 1]); // Swap elements if out of order
		}
	}
}

void PmergeMe::pairwiseSortDeque(std::deque<int> &container)
{
    // Step 1: Pairwise sorting - Deque
	// Pairwise sorting for a deque
	for (size_t i = 0; i < container.size() - 1; i += 2)
	{
		if (container[i] > container[i + 1])
		{
			std::swap(container[i], container[i + 1]); // Swap elements if out of order
		}
	}
}

void PmergeMe::handleOddElements(std::vector<int> &container)
{
    // Step 1: Handling odd elements - Vector
	// Handle odd elements in a vector
	int lastElement = container.back(); // Get the last element
	container.pop_back(); // Remove the last element
	insertSortVector(container, 0, container.size() - 1); // Sort the vector
	container.push_back(lastElement); // Put back the last element
}

void PmergeMe::handleOddElements(std::deque<int> &container)
{
    // Step 1: Handling odd elements - Deque
	// Handle odd elements in a deque
	int lastElement = container.back(); // Get the last element
	container.pop_back(); // Remove the last element
	insertSortDeque(container, 0, container.size() - 1); // Sort the deque
	container.push_back(lastElement); // Put back the last element
}


/*
** STEP 2
*/

void PmergeMe::fordJohnsonVector(std::vector<int> &container, int start, int end)
{
    // Step 2: Recursive sorting - Vector
	// Ford-Johnson algorithm for vector
	if (start < end)
	{
		int newEnd = start + (end - start) / 2;
		fordJohnsonVector(container, start, newEnd); // Recursively sort left half
		fordJohnsonVector(container, newEnd + 1, end); // Recursively sort right half
		mergeSortVector(container, start, newEnd, end); // Merge the sorted halves
		insertPendVector(container, start, newEnd, end); // Insert pend elements
	}
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &container, int start, int end)
{
    // Step 2: Recursive sorting - Deque
	// Ford-Johnson algorithm for deque
	if (start < end)
	{
		int newEnd = start + (end - start) / 2;
		fordJohnsonDeque(container, start, newEnd); // Recursively sort left half
		fordJohnsonDeque(container, newEnd + 1, end); // Recursively sort right half
		mergeSortDeque(container, start, newEnd, end); // Merge the sorted halves
		insertPendDeque(container, start, newEnd, end); // Insert pend elements
	}
}

/*
** STEP 3
*/

// Step 3: Merge sort - Vector
// Merge sort for vector
void PmergeMe::mergeSortVector(std::vector<int> &container, int start, int mid, int end)
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

// Step 3: Merge sort - Deque
// Merge sort for deque
void PmergeMe::mergeSortDeque(std::deque<int> &container, int start, int mid, int end)
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

// Step 3: Insert pend elements - Vector
// Insert pend elements into the sorted main chain for vector
void PmergeMe::insertPendVector(std::vector<int> &container, int start, int mid, int end)
{
    // Create a temporary vector to hold pend elements
    std::vector<int> pendElements;

    // Traverse the sorted main chain to find pend positions
    size_t i = start;
    size_t j = mid + 1;
    while (i <= static_cast<size_t>(mid) && j <= static_cast<size_t>(end))
    {
        if (container[i] > container[j])
        {
            pendElements.push_back(container[j]);
            j++;
        }
        else
        {
            i++;
        }
    }

    // Insert pend elements into the sorted main chain
    size_t pendIndex = start;
    int jacobsthalIndex = 1; // Initialize Jacobsthal number index
    for (int pendElement : pendElements)
    {
        // Check if the current index is a power of 2 minus 1
        if ((pendIndex & (pendIndex + 1)) == 0)
        {
            // Insert the pend element before the current index
            container[pendIndex - 1] = pendElement;
        }
        else
        {
            // Insert the pend element at the current index
            container[pendIndex] = pendElement;
        }
        pendIndex += jacobsthal(jacobsthalIndex++); // Update pendIndex based on Jacobsthal number sequence
    }
}

// Step 3: Insert pend elements - Deque
// Insert pend elements into the sorted main chain for deque
void PmergeMe::insertPendDeque(std::deque<int> &container, int start, int mid, int end)
{
    // Create a temporary deque to hold pend elements
    std::deque<int> pendElements;

    // Traverse the sorted main chain to find pend positions
    size_t i = start;
    size_t j = mid + 1;
    while (i <= static_cast<size_t>(mid) && j <= static_cast<size_t>(end))
    {
        if (container[i] > container[j])
        {
            pendElements.push_back(container[j]);
            j++;
        }
        else
        {
            i++;
        }
    }

    // Insert pend elements into the sorted main chain
    size_t pendIndex = start;
    int jacobsthalIndex = 1; // Initialize Jacobsthal number index
    for (int pendElement : pendElements)
    {
        // Check if the current index is a power of 2 minus 1
        if ((pendIndex & (pendIndex + 1)) == 0)
        {
            // Insert the pend element before the current index
            container[pendIndex - 1] = pendElement;
        }
        else
        {
            // Insert the pend element at the current index
            container[pendIndex] = pendElement;
        }
        pendIndex += jacobsthal(jacobsthalIndex++); // Update pendIndex based on Jacobsthal number sequence
    }
}

// Step 3: Insert pend elements - Deque
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

// Step 3: Insert pend elements - Deque
// Compute the n-th Jacobsthal number
int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

// Step 3: Insert pend elements - Vector
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


/*
** PRINTING
*/

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
