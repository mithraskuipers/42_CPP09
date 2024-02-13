/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PmergeMe.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 12:31:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/01/03 21:58:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_PROCESSOR_H
#define MERGE_PROCESSOR_H

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <sys/time.h>
#include <unistd.h> 

class PmergeMe
{
    public:
        PmergeMe ();
        PmergeMe (const PmergeMe &other);
        ~PmergeMe ();
        PmergeMe& operator=(const PmergeMe& other);
};

#endif