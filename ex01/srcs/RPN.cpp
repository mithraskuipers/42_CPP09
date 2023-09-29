/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RPN.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/15 16:00:02 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/29 14:07:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// Constructor
RPNCalculator::RPNCalculator()
{
	
}

// Parameterized Constructor
RPNCalculator::RPNCalculator(const std::string& expression)
{
	try																			// Initialize the calculator with the provided expression
	{
		int result = parseExpression(expression);
		this->operandStack.push(result);
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;									// Handle any exceptions if evaluation fails
	}
}

// Destructor
RPNCalculator::~RPNCalculator()
{
	while (!this->operandStack.empty())											// Clear the operand stack
	{
		this->operandStack.pop();
	}
}

/*
Standard containers, like std::stack, already provide deep copying behavior through their built-in copy constructor and assignment operator.
*/

// Copy Constructor (deep copy using assignment operator)
RPNCalculator::RPNCalculator(const RPNCalculator& other)
{
	this->operandStack = other.operandStack;									// Deep copy using assignment operator
}

RPNCalculator& RPNCalculator::operator=(const RPNCalculator& other)
{
	if (this == &other)
	{
		return (*this);															// Avoid self-assignment
	}

	this->operandStack = other.operandStack;									// Use the assignment operator of std::stack to deep copy the operandStack

	return (*this);
}

// Check if token is operator
int RPNCalculator::isOperand(const std::string& token)
{
	if ((token != "+") && (token != "-") && (token != "*") && (token != "/"))
	{
		return (1);
	}
	return (0);
}

int RPNCalculator::performOperation(const std::string& operatorToken)
{
	int operand2 = this->operandStack.top();									// Return last added element
	this->operandStack.pop();													// Remove last added element. Shrink numbers stack.

	int operand1 = this->operandStack.top();;									// Return last added element
	this->operandStack.pop();;													// Remove last added element. Shrink numbers stack.

	if (operatorToken == "+")
	{
		return (operand1 + operand2);
	}
	else if (operatorToken == "-")
	{
		return (operand1 - operand2);
	}
	else if (operatorToken == "*")
	{
		return (operand1 * operand2);
	}
	else if (operatorToken == "/")
	{
		if (operand2 == 0)
		{
			throw (std::runtime_error("Error: Division by zero"));				// Throw an exception instead of using std::cerr
		}
		return (operand1 / operand2);
	}
	throw (std::invalid_argument("Error: Invalid operator"));					// Throw an exception for an invalid operatorToken
}

int RPNCalculator::parseExpression(const std::string& expression)
{
	std::istringstream	iss(expression);
	std::string			token;

	while (iss >> token)														// Iteratively read tokens from the expression
	{
		if ((isOperand(token)))													// If token operand (number)
		{
			int operand;														// We have an operand token
			std::istringstream(token) >> operand;								// Convert the operand token to an integer
			this->operandStack.push(operand);									// Push the operand onto the number stack (top of stack; i.e. at the end)
		}
		else 																	// If token is operator (+, -, *, /)
		{
			if (this->operandStack.size() < 2)
			{
				throw (std::invalid_argument("Error: Insufficient operands for operator " + token)); // Throw an exception for insufficient operands
			}
			int result = performOperation(token);
			this->operandStack.push(result);									// Push result onto the number stack (top of stack; i.e. at the end)
		}
	}
	// No more tokens left
	if (this->operandStack.size() == 1)											// Done!
	{
		return (this->operandStack.top());
	}
	else
	{
		throw std::invalid_argument("Error: Invalid expression");
	}
}

/*
Example flow:
Suppose the expression used is "1 2 3 + +"
operandStack [1, 2, 3]
"+" token processed
return (2 + 3) which is pushed to operandStack (top of stack; i.e. at the end)
operandStack [1, 5]
"+" token processed
return (1 + 5), which is pushed to operandStack (top of stack; i.e. at the end)
operandStack [6]
operandStack size is 1, so we are done
*/