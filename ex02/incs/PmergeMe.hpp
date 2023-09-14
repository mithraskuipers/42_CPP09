#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template <typename Container>
void mergeSort(Container& container);

template <typename Container>
void fordJohnsonSort(Container& container);

template <typename Container>
void printContainer(const Container& container);

#endif
