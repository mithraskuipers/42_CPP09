/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/29 14:07:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// NOTE: THIS CPP09 EX01 IMPLEMENTATION USES STD::STACK<INT>

#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <expression>\n";
        return 1;
    }

    try 
    {
        RPN calculator;
        calculator.processExpression(argv[1]);
    } 
    catch (const std::exception &e) 
    {
        std::cerr << "Error: " << e.what();
        return 1;
    }

    return 0;
}

/*
Example input and desired outputs from the subject

make re && ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42

make re && ./RPN "7 7 * 7 -"
42

make re && ./RPN "1 2 * 2 / 2 * 2 4 - +"
0

make re && ./RPN "(1 + 1)"
Error
*/