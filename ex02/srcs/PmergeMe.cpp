#include "../incs/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this == &other)
	{
		return *this;
	}
	return *this;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)(other);
}

// Helper function to calculate Jacobsthal number
int jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
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

void PmergeMe::runVector(std::vector<int> &container)
{
	fordJohnsonVector(container, 0, container.size() - 1);
}

void PmergeMe::runDeque(std::deque<int> &container)
{
	fordJohnsonDeque(container, 0, container.size() - 1);
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

void PmergeMe::trackTime(std::vector<int> &Vcontainer, std::deque<int> &Dcontainer, double &vecTime, double &deqTime)
{
	std::clock_t start = std::clock();
	PmergeMe::runVector(Vcontainer);
	std::clock_t end = std::clock();
	double elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
	vecTime = elapsed;
	start = std::clock();
	PmergeMe::runDeque(Dcontainer);
	end = std::clock();
	elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
	deqTime = elapsed;
}

void PmergeMe::print(std::vector<int> &vectorContainer, std::deque<int> &dequeContainer)
{
	static int i = 0;

	if (!i)
	{
		std::cout << "Vector before: " << std::endl;
	}
	else
	{
		std::cout << "Vector after: " << std::endl;
	}
	typedef typename std::vector<int>::const_iterator Viterator;
	for (Viterator vectorIteratior = vectorContainer.begin(); vectorIteratior != vectorContainer.end(); ++vectorIteratior)
	{
		std::cout << *vectorIteratior << " ";
	}
	std::cout << std::endl;

	if (!i)
	{
		std::cout << "Deque before: " << std::endl;
	}
	else
		std::cout << "Deque after: " << std::endl;
	typedef typename std::deque<int>::const_iterator Diterator;
	for (Diterator dequeIterator = dequeContainer.begin(); dequeIterator != dequeContainer.end(); ++dequeIterator)
	{
		std::cout << *dequeIterator << " ";
	}
	std::cout << std::endl;
	i++;
}
