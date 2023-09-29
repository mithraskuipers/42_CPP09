/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 15:59:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/29 14:07:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class RPNCalculator
{
	public:
		RPNCalculator();
		RPNCalculator(const std::string& expression);
		~RPNCalculator();
		RPNCalculator(const RPNCalculator& other);
		RPNCalculator& operator=(const RPNCalculator& other);
		int parseExpression(const std::string& expression);
	private:
		std::stack<int> operandStack;
		int isOperand(const std::string& token);
		int performOperation(const std::string& operatorToken);
};

#endif