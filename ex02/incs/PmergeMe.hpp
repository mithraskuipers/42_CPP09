/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/04 12:50:51 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

template <typename Container>
void mergeSort(Container& container);

template <typename Container>
void fordJohnsonSort(Container& container);

template <typename Container>
void printContainer(const Container& container);

#endif
