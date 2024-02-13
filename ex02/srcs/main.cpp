#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

/*
NOTE: THIS CPP09 EX02 IMPLEMENTATION USES:
(1) std::vector<unsigned int>
(2) std::deque<std::pair<unsigned int, unsigned int>
*/

/*
make re ; ./PmergeMe $(shuf -i 1-100 -n 10)
make re ; ./PmergeMe $(shuf -i 10-100 -n 30) ;
make re ; ./PmergeMe $(shuf -i 1-100000 -n 3000) ;
*/

bool isFlagSet = false;
unsigned int flagValue;

void merge(std::vector<unsigned int>& elements, unsigned int low, unsigned int mid, unsigned int high) {
    unsigned int n1 = mid - low + 1;
    unsigned int n2 = high - mid;

    // Create temporary vectors to hold the two halves
    std::vector<unsigned int> left(n1);
    std::vector<unsigned int> right(n2);

    // Copy data to temporary vectors left[] and right[]
    for (unsigned int i = 0; i < n1; ++i)
        left[i] = elements[low + i];
    for (unsigned int j = 0; j < n2; ++j)
        right[j] = elements[mid + 1 + j];

    // Merge the temporary vectors back into elements[low..high]
    unsigned int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            elements[k] = left[i];
            ++i;
        } else {
            elements[k] = right[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of left[], if there are any
    while (i < n1) {
        elements[k] = left[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of right[], if there are any
    while (j < n2) {
        elements[k] = right[j];
        ++j;
        ++k;
    }
}

void mergeInsertionSort(std::vector<unsigned int>& elements, unsigned int low, unsigned int high) {
    if (low < high) {
        unsigned int mid = (low + high) / 2;

        // Recursively sort the two halves
        mergeInsertionSort(elements, low, mid);
        mergeInsertionSort(elements, mid + 1, high);

        // Merge the sorted halves
        merge(elements, low, mid, high);
    }
}

void processRange(std::vector<std::pair<unsigned int, unsigned int> >& container, bool isFirstTime) {
    struct timeval start, end;
    long sec, micro;

    if (isFirstTime) {
        std::cout << "Before: ";
        for (size_t i = 0; i < container.size(); ++i) {
            std::cout << container[i].first << " " << container[i].second << " ";
        }
        std::cout << std::endl;
    }

    gettimeofday(&start, NULL);

    // Combine all elements into a single vector for sorting
    std::vector<unsigned int> elements;
    for (size_t i = 0; i < container.size(); ++i) {
        elements.push_back(container[i].first);
        elements.push_back(container[i].second);
    }

    // Sort the elements using the Ford-Johnson algorithm
    mergeInsertionSort(elements, 0, elements.size() - 1);

    // Print the sorted elements only if isFirstTime is true
    if (isFirstTime) {
        std::cout << "After:  ";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    micro = end.tv_usec - start.tv_usec;
    long diff = (sec * 1000000) + micro;
    std::cout << "Time to process a range of " << container.size() * 2 << " elements: " << diff << " us";
    if (!isFirstTime)
        std::cout << "\n";


}



void processRange(std::deque<std::pair<unsigned int, unsigned int> >& container, bool isFirstTime) {
    // Since we cannot use Ford-Johnson with a deque directly, we convert it to a vector and then call the existing processRange function.
    std::vector<std::pair<unsigned int, unsigned int> > vec(container.begin(), container.end());
    processRange(vec, isFirstTime);
}

int main(int argc, char* argv[]) {
    std::vector<std::pair<unsigned int, unsigned int> > vec;
    std::deque<std::pair<unsigned int, unsigned int> > dec;

    for (int i = 1; i < argc; i += 2) {
        unsigned int start = std::atoi(argv[i]);
        unsigned int end = std::atoi(argv[i + 1]);
        if (start > end) {
            std::swap(start, end);
        }
        vec.push_back(std::make_pair(start, end));
        dec.push_back(std::make_pair(start, end));
    }

    processRange(vec, true); // Print the initial user input for vector
    std::cout << std::endl;
    processRange(dec, false); // Do not print the initial user input for deque

    return 0;
}


