


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/17 19:01:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Utility function to check if a string contains only digits
size_t PmergeMe::isStringOnlyDigits(const char *s)
{
	size_t len = strlen(s);
	for (size_t i = 0; i < len; i++)
	{
		if (!isdigit(s[i]))
		{
			return (0);
		}
	}
	return (1);
}


// Default constructor
PmergeMe::PmergeMe()
{
}

// Destructor
PmergeMe::~PmergeMe()
{
}

// Parameterized constructor
PmergeMe::PmergeMe(std::list<int> _list, std::deque<int> _deque) : mList(_list), mDeque(_deque)
{
}

// Copy constructor
PmergeMe::PmergeMe(const PmergeMe &other)
{
	// Deep copy of the mList
	mList = other.mList;

	// Deep copy of the mDeque
	mDeque = other.mDeque;
}

// Assignment operator
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other) // Self-assignment check
	{
		// Deep copy of the mList
		mList = other.mList;

		// Deep copy of the mDeque
		mDeque = other.mDeque;
	}
	return (*this);
}



// Function to process command line arguments
void PmergeMe::takeArgs(int argc, char **argv)
{
    int n;
    int i = 1;

    // Check if the input consists only of digits and is non-negative
    while (i < argc)
    {
        if (!isStringOnlyDigits(argv[i]) || (n = atoi(argv[i])) < 0)
        {
            std::cerr << "Error" << std::endl;
            exit(1);
        }

        mList.push_back(n);
        mDeque.push_back(n);
        i++;
    }

    // Print the original list with or without cutoff
    std::cout << "Before: ";
    printListWithCutoff(mList);
    std::cout << std::endl;

    // Call mergeInsert to sort the elements using the Ford-Johnson algorithm
    if (debugMode)
    {
        std::cout << "\n=LIST=\n" << std::endl;
    }
    mergeInsert<std::list<int>>(mList.begin(), mList.end());
    if (debugMode)
    {
        std::cout << "\n=DEQUE=\n" << std::endl;
    }
    mergeInsert<std::deque<int>>(mDeque.begin(), mDeque.end());
    size = argc - 1;
}

// Function to perform sorting and measure time
void PmergeMe::mergeMe(int argc, char **argv)
{
    takeArgs(argc, argv);

    auto start_list = std::chrono::high_resolution_clock::now();
    insertionSort<std::list<int>>(mList.begin(), mList.end());
    auto end_list = std::chrono::high_resolution_clock::now();
    printTime(mList, start_list, end_list);

    auto start_deque = std::chrono::high_resolution_clock::now();
    insertionSort<std::deque<int>>(mDeque.begin(), mDeque.end());
    auto end_deque = std::chrono::high_resolution_clock::now();
    printTime(mDeque, start_deque, end_deque);
}

// Recursive function to perform merge-insertion sort
template <typename T>
void PmergeMe::mergeInsert(typename T::iterator p, typename T::iterator r)
{
    int n = std::distance(p, r);
    if (n <= 1)
    {
        return; // Base case: no need to sort if the range has 1 or fewer elements
    }
    else
    {
        typename T::iterator q = p;
        std::advance(q, n / 2);

        // Recursively sort the left and right halves
        if (debugMode)
        {
            std::cout << "Left half: ";
            printSortedRange<T>(p, q);
            std::cout << std::endl;

            std::cout << "Right half: ";
            printSortedRange<T>(q, r);
            std::cout << std::endl;
        }
        mergeInsert<T>(p, q);
        mergeInsert<T>(q, r);

        // Merge the sorted halves
        merge<T>(p, q, r);
    }
}

// Function to merge two sorted halves of a container
template <typename T>
void PmergeMe::merge(typename T::iterator p, typename T::iterator q, typename T::iterator r)
{
    std::vector<int> L(p, q);
    std::vector<int> R(q, r);

    typename T::iterator itA = p;
    typename std::vector<int>::iterator itL = L.begin();
    typename std::vector<int>::iterator itR = R.begin();

    std::vector<int> merged;

    while (itL != L.end() && itR != R.end())
    {
        if (*itL <= *itR)
        {
            merged.push_back(*itL);
            itL++;
        }
        else
        {
            merged.push_back(*itR);
            itR++;
        }
    }

    while (itL != L.end())
    {
        merged.push_back(*itL);
        itL++;
    }

    while (itR != R.end())
    {
        merged.push_back(*itR);
        itR++;
    }

    for (const auto &element : merged)
    {
        *itA = element;
        ++itA;
    }
}

// Function to perform insertion sort
template <typename T>
void PmergeMe::insertionSort(typename T::iterator p, typename T::iterator r)
{
    if (debugMode)
    {
        std::cout << "Before insertion sorting: ";
        printSortedRange<T>(p, r);
        std::cout << '\n';
    }

    typename T::iterator it = p;
    while (it != r)
    {
        typename T::iterator current = it;
        int temp = *it;
        typename T::iterator prev = it;
        typename T::iterator next = prev;
        next++;
        while (prev != p && *(--prev) > temp)
        {
            *current = *prev;
            current = prev;
        }
        *current = temp;
        current = next;
        it++;
    }

    if (!afterPrinted)
    {
        std::cout << "After:  ";
        afterPrinted = true;
        printSortedRangeWithCutoff<T>(p, r);
        std::cout << '\n';
    }
}



// Utility function to print a list with cutoff if enabled
void PmergeMe::printListWithCutoff(const std::list<int> &list) const
{
	if (cutoffMode && list.size() > 4)
	{
		auto it = list.begin();
		for (int i = 0; i < 4; ++i)
		{
			std::cout << *it++ << " ";
		}
		std::cout << "[..]";
	}
	else
	{
		for (auto num : list)
		{
			std::cout << num << " ";
		}
	}
}

// Utility function to print a sorted range with cutoff if enabled
template <typename T>
void PmergeMe::printSortedRangeWithCutoff(typename T::iterator p, typename T::iterator r)
{
	if (cutoffMode && std::distance(p, r) > 4)
	{
		auto it = p;
		for (int i = 0; i < 4; ++i)
		{
			std::cout << *it++ << " ";
		}
		std::cout << "[..]";
	}
	else
	{
		printSortedRange<T>(p, r);
	}
}

// Utility function to print a sorted range
template <typename T>
void PmergeMe::printSortedRange(typename T::iterator p, typename T::iterator r)
{
	for (auto it = p; it != r; ++it)
	{
		std::cout << *it << " ";
	}
}

// Utility function to print the time taken to process a range of elements
template <typename Container>
void PmergeMe::printTime(const Container &container, std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end)
{
	auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); // Duration in nanoseconds

	std::string containerType;
	if (typeid(Container) == typeid(std::list<int>))
	{
		containerType = "std::list";
	}
	else if (typeid(Container) == typeid(std::deque<int>))
	{
		containerType = "std::deque";
	}
	else
	{
		containerType = "Unknown";
	}

	// Get the number of elements in the container
	size_t numElements = container.size();

	// Use setprecision to set the number of decimal places for microseconds
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << numElements << " elements with " << containerType << " : " << static_cast<double>(duration_ns) / 1000.0 << " us\n";
}

