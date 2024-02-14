/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/14 20:48:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

const int K = 5; // Define your constant K value

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(std::list<int> _list, std::deque<int> _deque) : mList(_list), mDeque(_deque) {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	mList = other.mList;
	mDeque = other.mDeque;
	return (*this);
}

// Function to check if a string contains only digits
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

// Function to print the sorted input
template <typename T>
void PmergeMe::printSortedInput(const T &A)
{
	int count = 0;
	typename T::const_iterator it = A.begin();
	while (it != A.end() && count < 4)
	{
		std::cout << *it << " ";
		++it;
		++count;
	}
	if (A.size() > 4)
	{
		std::cout << "[..]";
	}
}

// Function to process command line arguments
void PmergeMe::takeArgs(int argc, char **argv)
{
	int n;
	int i = 1;
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
		i++;
	}

	std::cout << "Before: ";
	int count = 0;
	for (int j = 1; j < argc && count < 4; ++j)
	{
		std::cout << argv[j] << " ";
		++count;
	}
	if (argc > 5)
	{
		std::cout << "[..]";
	}
	std::cout << std::endl;

	// Call mergeInsert to sort the elements using the Ford-Johnson algorithm
	mergeInsert(mList, mList.begin(), mList.end());
	mergeInsert(mDeque, mDeque.begin(), mDeque.end());

	std::cout << "After:  ";
	printSortedInput(mList);

	std::cout << std::endl;

	size = argc - 1;
}

// Function to perform insertion sort
template <typename T>
void PmergeMe::insertionSort(T &A, int p, int r)
{
	typename T::iterator it = A.begin();
	typename T::iterator ite = A.begin();
	std::advance(it, p);
	std::advance(ite, r + 1);
	while (it != ite && it != A.end())
	{
		typename T::iterator current = it;
		int temp = *it;
		typename T::iterator prev = it;
		typename T::iterator next = prev;
		next++;
		while (prev != A.begin() && *(--prev) > temp)
		{
			*current = *prev;
			current = prev;
		}
		*current = temp;
		current = next;
		it++;
	}
}

// Function to print processing time
void PmergeMe::printTime(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> end, const std::string &type)
{
	auto timePassed = std::chrono::duration<double, std::micro>(end - start).count();
	std::cout << "Time to process a range of " << size << " elements with "
			  << type << " " << std::fixed << std::setprecision(5) << timePassed << " µs." << std::endl;
}

// Function to perform merge sort on std::list and std::deque
void PmergeMe::mergeMe(int argc, char **argv)
{
	takeArgs(argc, argv);

	auto start_list = std::chrono::high_resolution_clock::now();
	insertionSort(mList, 0, mList.size() - 1);
	auto end_list = std::chrono::high_resolution_clock::now();
	printTime(start_list, end_list, "std::list");

	auto start_deque = std::chrono::high_resolution_clock::now();
	insertionSort(mDeque, 0, mDeque.size() - 1);
	auto end_deque = std::chrono::high_resolution_clock::now();
	printTime(start_deque, end_deque, "std::deque");
}

// Function to merge and sort ranges in the merge step of merge sort
template <typename T>
void PmergeMe::merge(T &, typename T::iterator p, typename T::iterator q, typename T::iterator r)
{
	typename T::iterator i = p;
	typename T::iterator j = q;
	typename T::iterator k = p;

	std::vector<int> L;
	std::vector<int> R;

	for (typename T::iterator it = i; it != q; ++it)
	{
		L.push_back(*it);
	}
	for (typename T::iterator it = j; it != r; ++it)
	{
		R.push_back(*it);
	}

	typename std::vector<int>::iterator itL = L.begin();
	typename std::vector<int>::iterator itR = R.begin();

	while (itL != L.end() && itR != R.end())
	{
		if (*itL <= *itR)
		{
			*k = *itL;
			++itL;
		}
		else
		{
			*k = *itR;
			++itR;
		}
		++k;
	}

	while (itL != L.end())
	{
		*k = *itL;
		++itL;
		++k;
	}

	while (itR != R.end())
	{
		*k = *itR;
		++itR;
		++k;
	}
}

// Function to perform the merge-insertion step of merge sort
template <typename T>
void PmergeMe::mergeInsert(T &A, typename T::iterator p, typename T::iterator r)
{
	int n = std::distance(p, r);
	if (n <= K)
	{
		insertionSort(A, std::distance(A.begin(), p), std::distance(A.begin(), r) - 1);
	}
	else
	{
		typename T::iterator q = p;
		std::advance(q, n / 2);
		mergeInsert(A, p, q);
		mergeInsert(A, q, r);
		merge(A, p, q, r);
	}
}
