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

/*
make re ; ./PmergeMe $(shuf -i 1-100 -n 10)
make re ; ./PmergeMe $(shuf -i 10-100 -n 30) ;
make re ; ./PmergeMe $(shuf -i 1-100000 -n 3000) ;
*/

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

bool isFlagSet = false;
unsigned int flagValue;

template <typename T, typename S, typename V>
void processRange(int argc, T &container, S &cont, V &conta, char choice)
{
    struct timeval start, end;
    long sec, micro;

    gettimeofday(&start, NULL);
    for (int i = 0; i < argc; i++)
    {
        if (container[i].first > container[i].second)
            std::swap(container[i].first, container[i].second);
    }

    for (int i = 0; i < argc; i++)
        conta.push_back(container[i].first);

    for (int i = 0; i < argc; i++)
        cont.push_back(container[i].second);

    std::sort(conta.begin(), conta.end());

    for (typename S::iterator it = cont.begin(); it != cont.end(); ++it)
        conta.insert(std::lower_bound(conta.begin(), conta.end(), *it), *it);

    if (isFlagSet)
        conta.insert(std::lower_bound(conta.begin(), conta.end(), flagValue), flagValue);

    std::cout << "\nAfter  : ";
    for (typename V::iterator it = conta.begin(); it != conta.end(); ++it)
        std::cout << *it << " ";

    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    micro = end.tv_usec - start.tv_usec;
    long diff = (sec * 1000000) + micro;
    if (choice == 'v')
        std::cout << "\nTime to process a range of " << argc << " elements with std::vector : " << diff << " us" << "\n";
    if (choice == 'd')
        std::cout << "\nTime to process a range of " << argc << " elements with std::deque : " << diff << " us" << "\n";
}

void validateInput(char *arg1, char *arg2)
{
    if (std::atoi(arg1) < 0 || std::atoi(arg2) < 0)
    {
        std::cerr << "Invalid Input: Number Less Than 0\n";
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if ((argc - 1) % 2 != 0)
    {
        isFlagSet = true;
        flagValue = std::atoi(argv[argc - 1]);
        if (flagValue < 0)
            exit(1);
        argc -= 1;
    }

    std::cout << "Before : ";
    for (int i = 1; i < argc; i++)
        std::cout << argv[i] << " ";

    // VECTOR
    std::vector<std::pair<unsigned int, unsigned int> > vec;
    for (int i = 1; i < argc; i += 2)
    {
        if (isdigit(*argv[i]) && isdigit(*argv[i + 1]))
        {
            validateInput(argv[i], argv[i + 1]);
            vec.push_back(std::make_pair(std::atoi(argv[i]), std::atoi(argv[i + 1])));
        }
        else
        {
            std::cerr << "Invalid input: non-numeric argument.\n";
            return 1;
        }
    }
    std::vector<unsigned int> vec_a, vec_b;
    vec_a.reserve(vec.size());
    vec_b.reserve(vec.size());
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        vec_a.push_back(it->first);
        vec_b.push_back(it->second);
    }

    processRange(vec.size(), vec, vec_a, vec_b, 'v');

    // DEQUE
    std::deque<std::pair<unsigned int, unsigned int> > dec;
    for (int i = 1; i < argc; i += 2)
    {
        if (isdigit(*argv[i]) && isdigit(*argv[i + 1]))
        {
            validateInput(argv[i], argv[i + 1]);
            dec.push_back(std::make_pair(std::atoi(argv[i]), std::atoi(argv[i + 1])));
        }
        else
        {
            std::cerr << "Invalid input: non-numeric argument.\n";
            return 1;
        }
    }

    std::deque<unsigned int> dec_a, dec_b;
    for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = dec.begin(); it != dec.end(); ++it)
    {
        dec_a.push_back(it->first);
        dec_b.push_back(it->second);
    }

    processRange(dec.size(), dec, dec_a, dec_b, 'd');

    return 0;
}
