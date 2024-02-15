// PmergeMe.hpp

#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <chrono>
#include <cstring>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip> // For setprecision

class PmergeMe
{
private:
	std::list<int> mList;
	std::deque<int> mDeque;
	size_t size;
	bool afterPrinted = false;

public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(std::list<int> _list, std::deque<int> _deque);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);

template <typename Container>
void printTime(const Container& container, std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);

	void mergeMe(int argc, char **argv);
	size_t isStringOnlyDigits(const char *s);
	void takeArgs(int argc, char **argv);

	template <typename T>
	void mergeInsert(typename T::iterator p, typename T::iterator r);

	template <typename T>
	void insertionSort(typename T::iterator p, typename T::iterator r);

	template <typename T>
	void merge(typename T::iterator p, typename T::iterator q, typename T::iterator r);

	void printListWithCutoff(const std::list<int> &list) const;

	template <typename T>
	void printSortedRangeWithCutoff(typename T::iterator p, typename T::iterator r);

	template <typename T>
	void printSortedRange(typename T::iterator p, typename T::iterator r);
	void printSortedInput(const std::list<int> &sortedList);

	bool debugMode = false;
	bool cutoffMode = true;
};

#endif
