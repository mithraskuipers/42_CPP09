/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 12:31:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/12/30 00:24:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    // Constructor
}

PmergeMe::~PmergeMe()
{
    // Destructor
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    // Copy Constructor
    this->intVector = other.intVector;
    this->intDeque = other.intDeque;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    // Assignment Operator Overload
    if (this != &other)
    {
        this->intVector = other.intVector;
        this->intDeque = other.intDeque;
    }
    return (*this);
}

void PmergeMe::intVectorPrinter()
{
    // Print elements of intVector
    for (std::vector<int>::iterator it = intVector.begin(); it != intVector.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::intDequePrinter()
{
    // Print elements of intDeque
    for (std::deque<int>::iterator it = intDeque.begin(); it != intDeque.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::readInput(char **argv)
{
    // Read input values from command line arguments and populate intVector and intDeque
    for (int left_idx = 1; argv[left_idx]; left_idx++)
    {
        this->intVector.push_back(std::atoi(argv[left_idx]));
        this->intDeque.push_back(std::atoi(argv[left_idx]));
    }
}

void PmergeMe::fordJohnsonSortWrapper()
{
    // Wrapper function to demonstrate sorting for both std::vector and std::deque

    // Sorting using std::vector
    std::cout << "Before sorting (std::vector): ";
    this->intVectorPrinter();
    clock_t start = clock();
    this->fordJohnsonSort(this->intVector, 0, this->intVector.size() - 1);
    clock_t stop = clock();
    std::cout << "After sorting (std::vector): ";
    this->intVectorPrinter();
    double duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000;
    std::cout << "Time to sort (std::vector): " << duration << " us" << std::endl;

    // Sorting using std::deque
    std::cout << "Before sorting (std::deque): ";
    this->intDequePrinter();
    start = clock();
    this->fordJohnsonSort(this->intDeque, 0, this->intDeque.size() - 1);
    stop = clock();
    std::cout << "After sorting (std::deque): ";
    this->intDequePrinter();
    duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000;
    std::cout << "Time to sort (std::deque): " << duration << " us" << std::endl;
}



template <typename T>
void PmergeMe::mergeSublists(T &lst, int lst_start_idx, int mid, int lst_end_idx)
{
    // Merge sublists into a temporary vector
    int left_idx = lst_start_idx;
    int right_index = mid + 1;
    int temp_index = 0;
    std::vector<int> temp(lst_end_idx - lst_start_idx + 1);

    std::cout << "Merging and sorting sublists: <";
    while (left_idx <= mid && right_index <= lst_end_idx)
    {
        if (lst[left_idx] <= lst[right_index])
        {
            std::cout << lst[left_idx];
            temp[temp_index++] = lst[left_idx++];
        }
        else
        {
            std::cout << lst[right_index];
            temp[temp_index++] = lst[right_index++];
        }

        if (left_idx <= mid || right_index <= lst_end_idx)
        {
            std::cout << ", ";
        }
    }
    std::cout << ">" << std::endl;

    while (left_idx <= mid)
    {
        temp[temp_index++] = lst[left_idx++];
    }

    while (right_index <= lst_end_idx)
    {
        temp[temp_index++] = lst[right_index++];
    }

    for (int p = 0; p < temp_index; p++)
    {
        lst[lst_start_idx + p] = temp[p];
    }

    std::cout << "Sorted sublist from index " << lst_start_idx << " to " << lst_end_idx << ": ";
    for (int i = lst_start_idx; i <= lst_end_idx; ++i)
    {
        std::cout << lst[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe::fordJohnsonSort(T &lst, int lst_start_idx, int lst_end_idx)
{
    // Recursive merge-sort implementation

    int lst_mid_idx;

    if (lst_start_idx != lst_end_idx)
    {
        // If sublist has more than one item, continue dividing it
        lst_mid_idx = lst_start_idx + ((lst_end_idx - lst_start_idx) / 2);

        // Left sublist
        std::cout << "Sorting left sublist from index " << lst_start_idx << " to " << lst_mid_idx << ": ";
        for (int i = lst_start_idx; i <= lst_mid_idx; ++i)
        {
            std::cout << lst[i] << " ";
        }
        std::cout << std::endl;
        fordJohnsonSort(lst, lst_start_idx, lst_mid_idx);

        // Right sublist
        std::cout << "Sorting right sublist from index " << lst_mid_idx + 1 << " to " << lst_end_idx << ": ";
        for (int i = lst_mid_idx + 1; i <= lst_end_idx; ++i)
        {
            std::cout << lst[i] << " ";
        }
        std::cout << std::endl;
        fordJohnsonSort(lst, lst_mid_idx + 1, lst_end_idx);

        // Merge the sorted halves back together
        std::cout << "Merging sublists from index " << lst_start_idx << " to " << lst_mid_idx
                  << " and from index " << lst_mid_idx + 1 << " to " << lst_end_idx << std::endl;
        mergeSublists(lst, lst_start_idx, lst_mid_idx, lst_end_idx);
    }
}


// Explicit instantiation of template for specific types
template void PmergeMe::fordJohnsonSort(std::vector<int> &lst, int lst_start_idx, int lst_end_idx);
template void PmergeMe::fordJohnsonSort(std::deque<int> &lst, int lst_start_idx, int lst_end_idx);
