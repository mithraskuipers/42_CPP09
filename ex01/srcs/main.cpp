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

#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <inverted Polish expression>" << std::endl;
		return (1);
	}
	int	outcome;
	try
	{
		RPNCalculator	calculator;
		outcome = calculator.parseExpression(argv[1]);
		std::cout << outcome << std::endl;
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl; // Used to output errors
		return (1);
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