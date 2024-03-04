/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/23 21:06:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

class PmergeMe
{
public:
    PmergeMe();
    ~PmergeMe();

    void wrapper(std::vector<int> &Vcontainer, std::deque<int> &Dcontainer, uint &vecTime, uint &deqTime);

    void pairwiseSortVector(std::vector<int> &container);
    void pairwiseSortDeque(std::deque<int> &container);
    void handleOddElements(std::vector<int> &container);
    void handleOddElements(std::deque<int> &container);

    void recursiveSortingVector(std::vector<int> &container, int start, int end);
    void recursiveSortingDeque(std::deque<int> &container, int start, int end);

    void mergeSortedHalvesVector(std::vector<int> &container, int start, int mid, int end);
    void mergeSortedHalvesDeque(std::deque<int> &container, int start, int mid, int end);

    void insertPendVector(std::vector<int> &container, int start, int mid, int end);
    void insertPendDeque(std::deque<int> &container, int start, int mid, int end);

    void insertSortDeque(std::deque<int> &container, int start, int end);
    void insertSortVector(std::vector<int> &container, int start, int end);

    void printVector(const std::vector<int> &vectorContainer, bool isBefore);
    void printDeque(const std::deque<int> &dequeContainer, bool isBefore);

    int jacobsthal(int n);

    // For debugging
    void printPendElementsVector(const std::vector<int> &pendElements);
    void printPendElementsDeque(const std::deque<int> &pendElements);
};

#endif