/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/14 22:55:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
NOTE: THIS CPP09 EX02 IMPLEMENTATION USES:
(1) std::list
(2) std::deque
*/

/*
SOURCE:
https://en.wikipedia.org/wiki/Merge-insertion_sort
*/

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " n1 n2 n3 ..." << std::endl;
        return (1);
    }
    PmergeMe p;
    p.mergeMe(argc, argv);
    return (0);
}
