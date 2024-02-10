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

'''
NOTE: THIS CPP09 EX01 IMPLEMENTATION USES:
std::stack<int>
'''

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

/*
Example flow for expression:
"8 9 * 9 - 9 - 9 - 4 - 1 +"

Push 8 onto the stack: [8]
Push 9 onto the stack: [8, 9]
Perform multiplication of top two operands (8 and 9): 8 * 9 = 72.
Remove 8 and 9 using pop(), and push 72 onto the stack: [72]
Push 9 onto the stack: [72, 9]
Perform subtraction of top two operands (72 and 9): 72 - 9 = 63.
Remove 72 and 9 using pop(), and push 63 onto the stack: [63]
Push 9 onto the stack: [63, 9]
Perform subtraction of top two operands (63 and 9): 63 - 9 = 54.
Remove 63 and 9 using pop(), and push 54 onto the stack: [54]
Push 9 onto the stack: [54, 9]
Perform subtraction of top two operands (54 and 9): 54 - 9 = 45.
Remove 54 and 9 using pop(), and push 45 onto the stack: [45]
Push 4 onto the stack: [45, 4]
Perform subtraction of top two operands (45 and 4): 45 - 4 = 41.
Remove 45 and 4 using pop(), and push 41 onto the stack: [41]
Push 1 onto the stack: [41, 1]
Perform addition of top two operands (41 and 1): 41 + 1 = 42.
Remove 41 and 1 using pop(), and push 42 onto the stack: [42]
The final result is 42, which is outputted by the program.
*/