/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:09:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/10/05 21:39:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool isPositiveNumber(const std::string &s)
{
    if (s.empty() || (s[0] == '0' && s.length() > 1))
	{
        return false; // Numbers starting with 0 are not positive
    }
    for (std::size_t i = 0; i < s.length(); ++i)
	{
        if (!std::isdigit(s[i]))
		{
            return false; // Non-digit characters found
        }
    }
    return (true);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
	{
        std::cout << "Usage: " << argv[0] << " <positive_number_sequence>" << std::endl;
        return 1;
    }

    std::string input(argv[1]);

    if (isPositiveNumber(input))
	{
        std::cout << "The input sequence is correct and consists of positive numbers." << std::endl;
    }
	else
	{
        std::cout << "Invalid input. Please enter a valid positive number sequence." << std::endl;
    }

    return (0);
}


/*
make re && ./PmergeMe 3 5 9 7 4 ;
make re && ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "` ;
*/