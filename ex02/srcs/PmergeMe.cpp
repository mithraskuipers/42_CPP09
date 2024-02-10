/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/01/22 14:21:35 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe ()
{
}

PmergeMe::PmergeMe (const PmergeMe &other)
{
        this->operator=(other);
}

PmergeMe::~PmergeMe ()
{
}

PmergeMe& PmergeMe::operator = (const PmergeMe& other)
{
        (void)other;
        return(*this);
}
