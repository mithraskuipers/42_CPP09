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

class PmergeMe {
private:
    std::list<int> mList;
    std::deque<int> mDeque;
    size_t size;

public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(std::list<int> _list, std::deque<int> _deque);
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

    void printTime(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, const std::string& label);
    void mergeMe(int argc, char **argv);
    size_t isStringOnlyDigits(const char *s);
    void takeArgs(int argc, char **argv);

    template <typename T>
    void mergeInsert(typename T::iterator p, typename T::iterator r);

    template <typename T>
    void insertionSort(typename T::iterator p, typename T::iterator r);

    template <typename T>
    void merge(typename T::iterator p, typename T::iterator q, typename T::iterator r);



	template <typename T>
	void printSortedRange(typename T::iterator p, typename T::iterator r);
    void printSortedInput(const std::list<int>& sortedList);
};

#endif // PMERGE_ME_HPP
