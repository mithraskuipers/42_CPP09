// PmergeMe.hpp

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstddef>

#define VERBOSEMODE 1

class PmergeMe
{
public:
    // Constructor and Destructor
    PmergeMe();
    ~PmergeMe();

    // Methods to handle odd elements
    void handleOddElements(std::vector<int> &container);
    void handleOddElements(std::deque<int> &container);

    // Wrapper method
    void wrapper(std::vector<int> &Vcontainer, std::deque<int> &Dcontainer, uint &vecTime, uint &deqTime);

    // Vector sorting methods
    void fordJohnsonVector(std::vector<int> &container, int start, int end);
    void mergeSortVector(std::vector<int> &container, int start, int mid, int end);
    void insertSortVector(std::vector<int> &container, int start, int end);

    // Deque sorting methods
    void fordJohnsonDeque(std::deque<int> &container, int start, int end);
    void mergeSortDeque(std::deque<int> &container, int start, int mid, int end);
    void insertSortDeque(std::deque<int> &container, int start, int end);

    // Utility methods
    void printVector(const std::vector<int> &vectorContainer, bool isBefore);
    void printDeque(const std::deque<int> &dequeContainer, bool isBefore);
    static int jacobsthal(int n);

	void pairwiseSortVector(std::vector<int> &container);
	void pairwiseSortDeque(std::deque<int> &container);

	void insertPendVector(std::vector<int> &container, int start, int mid, int end);
	void insertPendDeque(std::deque<int> &container, int start, int mid, int end);

};

#endif
