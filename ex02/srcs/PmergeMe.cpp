#include "PmergeMe.hpp"

const int K = 5; // Define your constant K value

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(std::list<int> _list, std::deque<int> _deque) : mList(_list), mDeque(_deque) {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	mList = other.mList;
	mDeque = other.mDeque;
	return (*this);
}

void PmergeMe::mergeMe(int argc, char **argv)
{
	takeArgs(argc, argv);

	auto start_list = std::chrono::high_resolution_clock::now();
	insertionSort<std::list<int>>(mList.begin(), mList.end());
	auto end_list = std::chrono::high_resolution_clock::now();
	printTime(start_list, end_list, "std::list");

	auto start_deque = std::chrono::high_resolution_clock::now();
	insertionSort<std::deque<int>>(mDeque.begin(), mDeque.end());
	auto end_deque = std::chrono::high_resolution_clock::now();
	printTime(start_deque, end_deque, "std::deque");
}

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

		// Print the original values that will be split
		std::cout << "Original values: ";
		printSortedRange<T>(p, r);
		std::cout << '\n';

		std::cout << "Splitting range into two subranges...\n";

		// Print the left set
		std::cout << "Left set: ";
		printSortedRange<T>(p, q);
		std::cout << '\n';

		// Print the right set
		std::cout << "Right set: ";
		printSortedRange<T>(q, r);
		std::cout << '\n';

		mergeInsert<T>(p, q);
		mergeInsert<T>(q, r);

		// Print how it is being processed and sorted
		std::cout << "Sorting sets: ";
		printSortedRange<T>(p, q);
		std::cout << "and ";
		printSortedRange<T>(q, r);
		std::cout << '\n';

		merge<T>(p, q, r);
	}
}

void PmergeMe::printTime(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, const std::string &label)
{
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << label << " duration: " << duration.count() << " microseconds\n";
}

template <typename T>
void PmergeMe::printSortedRange(typename T::iterator p, typename T::iterator r)
{
	for (auto it = p; it != r; ++it)
	{
		std::cout << *it << " ";
	}
}

void PmergeMe::takeArgs(int argc, char **argv)
{
	int n;
	int i = 1;
	std::cout << "Before sorting: ";
	while (i < argc)
	{
		n = atoi(argv[i]);
		if (!isStringOnlyDigits(argv[i]) || n < 0)
		{
			std::cerr << "Error" << std::endl;
			exit(1);
		}
		mList.push_back(n);
		mDeque.push_back(n);
		std::cout << n << " "; // Print each element as it is added
		i++;
	}
	std::cout << std::endl; // Add newline after printing the original sequence

	// Call mergeInsert to sort the elements using the Ford-Johnson algorithm
	std::cout << "Sorting using mergeInsert algorithm...\n";
	mergeInsert<std::list<int>>(mList.begin(), mList.end());
	std::cout << "============================================================================" << std::endl;
	mergeInsert<std::deque<int>>(mDeque.begin(), mDeque.end());
	std::cout << "============================================================================" << std::endl;

	size = argc - 1;
}

template <typename T>
void PmergeMe::insertionSort(typename T::iterator p, typename T::iterator r)
{
	std::cout << "Before insertion sorting: ";
	printSortedRange<T>(p, r);
	std::cout << '\n';

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
	std::cout << "After insertion sorting: ";
	printSortedRange<T>(p, r);
	std::cout << '\n';
}

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
		std::cout << "Comparing: " << *itL << " with " << *itR << '\n';
		if (*itL <= *itR)
		{
			std::cout << *itL << " is smaller, adding it to the merged result.\n";
			merged.push_back(*itL);
			std::cout << "Current merged result: ";
			printSortedRange<std::vector<int>>(merged.begin(), merged.end());
			std::cout << '\n';
			++itL;
		}
		else
		{
			std::cout << *itR << " is smaller, adding it to the merged result.\n";
			merged.push_back(*itR);
			std::cout << "Current merged result: ";
			printSortedRange<std::vector<int>>(merged.begin(), merged.end());
			std::cout << '\n';
			++itR;
		}
	}

	while (itL != L.end())
	{
		merged.push_back(*itL);
		++itL;
	}

	while (itR != R.end())
	{
		merged.push_back(*itR);
		++itR;
	}

	for (const auto &element : merged)
	{
		*itA = element;
		++itA;
	}

	// Print the merged result
	std::cout << "Merged result: ";
	printSortedRange<T>(p, r);
	std::cout << '\n';
}
