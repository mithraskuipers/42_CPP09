#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    this->intVector = other.intVector;
    this->intDeque = other.intDeque;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        this->intVector = other.intVector;
        this->intDeque = other.intDeque;
    }
    return (*this);
}

static bool printOutput = true;

void PmergeMe::intVectorPrinter()
{
    for (std::vector<int>::iterator it = intVector.begin(); it != intVector.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::intDequePrinter()
{
    for (std::deque<int>::iterator it = intDeque.begin(); it != intDeque.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::setPrintOutput(bool enablePrint)
{
    printOutput = enablePrint;
}

void PmergeMe::readInput(char **argv)
{
    for (int left_idx = 1; argv[left_idx]; left_idx++)
    {
        this->intVector.push_back(std::atoi(argv[left_idx]));
        this->intDeque.push_back(std::atoi(argv[left_idx]));
    }
}

void PmergeMe::fordJohnsonSortWrapper()
{
    double duration;
    clock_t start, stop;

    std::cout << "Before: ";
    this->intVectorPrinter();
    start = clock();
    this->fordJohnsonSort(this->intVector, 0, this->intVector.size() - 1);
    stop = clock();
    std::cout << "After:  ";
    this->intVectorPrinter();
    duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000;
    std::cout << "Time to processExpression a range of " << this->intVector.size() << " elements with std::vector: ";
    std::cout << duration << " us" << std::endl;

    start = clock();
    this->fordJohnsonSort(this->intDeque, 0, this->intDeque.size() - 1);
    stop = clock();
    duration = ((stop - start) / (double)CLOCKS_PER_SEC) * 1000000;
    std::cout << "Time to processExpression a range of " << this->intDeque.size() << " elements with std::deque: ";
    std::cout << duration << " us" << std::endl;
}


template <typename T>
void PmergeMe::mergeSublists(T &lst, int lst_start_idx, int mid, int lst_end_idx)
{
    // Merge sublists in-place
    int left_idx = lst_start_idx;
    int right_idx = mid + 1;

    // Temporary vector to store merged sublists
    std::vector<int> temp(lst_end_idx - lst_start_idx + 1);
    int temp_index = 0;

    if (printOutput)
    {
        std::cout << "Merging sublists: <";

        for (int i = lst_start_idx; i <= mid; ++i)
        {
            std::cout << lst[i];
            if (i < mid)
                std::cout << ", ";
        }

        std::cout << "> <";

        for (int i = mid + 1; i <= lst_end_idx; ++i)
        {
            std::cout << lst[i];
            if (i < lst_end_idx)
                std::cout << ", ";
        }
    }

    while (left_idx <= mid && right_idx <= lst_end_idx)
    {
        if (lst[left_idx] <= lst[right_idx])
        {
            temp[temp_index++] = lst[left_idx++];
        }
        else
        {
            temp[temp_index++] = lst[right_idx++];
        }
    }

    while (left_idx <= mid)
    {
        temp[temp_index++] = lst[left_idx++];
    }

    while (right_idx <= lst_end_idx)
    {
        temp[temp_index++] = lst[right_idx++];
    }

    if (printOutput)
    {
        std::cout << ">" << std::endl;
    }

    // Print the intermediate state of the list after merging each pair of sublists
    if (printOutput)
    {
        std::cout << "Merged state: ";
		std::cout << "<";
        for (int i = lst_start_idx; i <= lst_end_idx; ++i)
        {
            std::cout << lst[i];
            if (i < lst_end_idx)
                std::cout << ", ";
        }
		std::cout << ">";
        std::cout << std::endl;
    }

    // Copy sorted elements back to the original list
    for (int i = 0; i < temp_index; i++)
    {
        lst[lst_start_idx + i] = temp[i];
    }

    if (printOutput)
    {
        std::cout << "Sorted sublist: <";
        for (int i = lst_start_idx; i <= lst_end_idx; ++i)
        {
            std::cout << lst[i];
            if (i < lst_end_idx)
                std::cout << ", ";
        }
        std::cout << ">" << std::endl;
    }
}





template <typename T>
void PmergeMe::fordJohnsonSort(T &lst, int lst_start_idx, int lst_end_idx)
{
    int lst_mid_idx;

    if (lst_start_idx != lst_end_idx)
    {
        lst_mid_idx = lst_start_idx + ((lst_end_idx - lst_start_idx) / 2);

        if (printOutput)
        {
            std::cout << "Splitting list: <";
            for (int i = lst_start_idx; i <= lst_end_idx; ++i)
            {
                std::cout << lst[i];
                if (i < lst_end_idx)
                    std::cout << ", ";
            }
            std::cout << ">" << std::endl;
        }

        fordJohnsonSort(lst, lst_start_idx, lst_mid_idx);
        fordJohnsonSort(lst, lst_mid_idx + 1, lst_end_idx);

        mergeSublists(lst, lst_start_idx, lst_mid_idx, lst_end_idx);
    }
}



// Explicit instantiation of template for specific types
template void PmergeMe::fordJohnsonSort(std::vector<int> &lst, int lst_start_idx, int lst_end_idx);
template void PmergeMe::fordJohnsonSort(std::deque<int> &lst, int lst_start_idx, int lst_end_idx);
