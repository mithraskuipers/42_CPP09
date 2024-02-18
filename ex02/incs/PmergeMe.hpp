#ifndef P_HPP
#define P_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstddef>

#define START(x) x + 1

class PmergeMe
{
public:
    // Orthodox Canonical Form
    PmergeMe();
    ~PmergeMe();
    PmergeMe &operator=(const PmergeMe &other);
    PmergeMe(const PmergeMe &other);

    // Vector sort functions
    static void fordJohnsonVector(std::vector<int> &container, int start, int end);
    static void mergeSortVector(std::vector<int> &container, int start, int mid, int end);
    static void insertSortVector(std::vector<int> &container, int start, int end);

    // Deque sort functions
    static void fordJohnsonDeque(std::deque<int> &container, int start, int end);
    static void mergeSortDeque(std::deque<int> &container, int start, int mid, int end);
    static void insertSortDeque(std::deque<int> &container, int start, int end);

    // Calculate time functions
    static void runVector(std::vector<int> &container);
    static void runDeque(std::deque<int> &container);

    // Utility functions
    static void print(std::vector<int> &, std::deque<int> &);
    static void trackTime(std::vector<int> &, std::deque<int> &, double &, double &);
    static int findSplitIndex(int start, int end);
};

#endif
