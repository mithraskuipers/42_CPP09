/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 15:59:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/22 17:54:55 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_H
#define RPN_H

#include <iostream> // for stdin and stdout operations
#include <stack>	// to use the stack container
#include <cstdlib>	// to use exit()

class RPN
{
public:
	RPN();
	RPN(const RPN &a);
	~RPN();
	RPN &operator=(const RPN &a);
	void processExpression(std::string input);
	int calculate(int leftNumber, int rightNumber, char o);
	void printStack(const std::stack<int>& stackToPrint) const;

	bool debugMode;

private:
	std::stack<int> _stack;
};

#endif