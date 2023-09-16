/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/16 19:13:28 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Container>
void merge(Container& /*arr*/, typename Container::iterator left, typename Container::iterator middle, typename Container::iterator right) {
    Container L(left, middle);
    Container R(middle, right);

    typename Container::iterator i = L.begin();
    typename Container::iterator j = R.begin();
    typename Container::iterator k = left;

    while (i != L.end() && j != R.end()) {
        if (*i <= *j) {
            *k = *i;
            ++i;
        } else {
            *k = *j;
            ++j;
        }
        ++k;
    }

    while (i != L.end()) {
        *k = *i;
        ++i;
        ++k;
    }

    while (j != R.end()) {
        *k = *j;
        ++j;
        ++k;
    }
}

template <typename Container>
void mergeSort(Container& container, typename Container::iterator left, typename Container::iterator right)
{
    if (std::distance(left, right) > 1)
	{
        typename Container::iterator middle = left;
        std::advance(middle, std::distance(left, right) / 2);

        mergeSort(container, left, middle);
        mergeSort(container, middle, right);

        merge(container, left, middle, right);
    }
}

template <typename Container>
void fordJohnsonSort(Container& container)
{
    if (container.empty())
	{
        return; // Nothing to sort
    }

    typename Container::iterator min_it = std::min_element(container.begin(), container.end());
    typename Container::iterator max_it = std::max_element(container.begin(), container.end());

    int min = *min_it;
    int max = *max_it;

    if (min < 0) {
        // Shift the elements to make them all non-negative
        int shift = -min;
        for (typename Container::iterator it = container.begin(); it != container.end(); ++it) {
            *it += shift;
        }
        max += shift;
    }

    std::vector<int> aux(max + 1, 0);

    for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it) {
        aux[*it]++;
    }

    container.clear();

    for (int i = 0; i <= max; i++)
	{
        for (int j = 0; j < aux[i]; j++) {
            container.push_back(i);
        }
    }

    if (min < 0) {
        // Shift the elements back to their original values
        int shift = -min;
        for (typename Container::iterator it = container.begin(); it != container.end(); ++it) {
            *it -= shift;
        }
    }
}

template <typename Container>
void printContainer(const Container& container)
{
    for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}

// Explicit template instantiations for int vectors and lists
template void mergeSort(std::vector<int>& container, typename std::vector<int>::iterator left, typename std::vector<int>::iterator right);
template void fordJohnsonSort(std::vector<int>& container);
template void printContainer(const std::vector<int>& container);
template void mergeSort(std::list<int>& container, typename std::list<int>::iterator left, typename std::list<int>::iterator right);
template void fordJohnsonSort(std::list<int>& container);
template void printContainer(const std::list<int>& container);
