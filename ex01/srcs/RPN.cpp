#include "RPN.hpp"

// Default constructor
RPN::RPN() {
}

// Copy constructor
RPN::RPN(const RPN &a) {
    this->_outcome = a._outcome; // Copy the stack from 'a' to the current object
}

// Destructor
RPN::~RPN() {
}

// Assignment operator
RPN &RPN::operator=(const RPN &a)
{
    if (this != &a) // Check for self-assignment
	{
        this->_outcome = a._outcome; // Copy the stack from 'a' to the current object
    }
    return *this;
}

// Perform arithmetic operations based on operators
int RPN::calculate(int leftNumber, int rightNumber, char o) 
{
    switch (o) 
    {
        case '+': 
        {
            return (leftNumber + rightNumber);
        }
        case '-': 
        {
            return (rightNumber - leftNumber);
        }
        case '*': 
        {
            return (leftNumber * rightNumber);
        }
        case '/': 
        {
            if (rightNumber == 0) 
            {
                throw std::invalid_argument("Error\n"); // Division by zero :-)
            }
            return (rightNumber / leftNumber);
        }
    }
    return 0;
}

// Read input string and perform RPN (Reverse Polish Notation) calculation
void RPN::processExpression(std::string input) {
    // The set of operators to consider
    std::string operator_set = "+/*-";

    // Variables to count operators and numbers
    size_t n_operators = 0;
    size_t n_operands = 0;

    // Loop through the input string
    for (size_t i = 0; i < input.length(); i++) {
        // If the current character is a numeric operator
        if (isdigit(input[i])) {
            // Increment the number count
            n_operands++;
            // Convert the character to an integer and push it onto the stack
            this->_outcome.push(input[i] - '0');
        } 
        // If the current character is an arithmetic operator
        else if (operator_set.find(input[i]) != std::string::npos) {
            // Increment the operator count
            n_operators++;
            // Check if the stack has at least two operands to perform the operation
            if (_outcome.size() < 2) {
                throw std::invalid_argument("Not enough operands for operator\n");
            }
            // Pop (retrieve and remove) the top two numbers from the stack and perform the calculation
            int leftNumber = _outcome.top();
            _outcome.pop();
            _outcome.top() = calculate(leftNumber, _outcome.top(), input[i]);
        } 
        // If the current character is a space, skip it
        else if (isspace(input[i])) {
            continue;
        } 
        // If the current character is not recognized (neither digit, operator, nor space), throw an error
        else {
            throw std::invalid_argument("Current character is not recognized as digit, operator, nor space\n");
        }
    }
    // Check if the number of operators is one less than the number of numbers
    if ((n_operators + 1) != n_operands) {
        throw std::invalid_argument("Number of operators less or greater than numbers\n");
    }

    // Output the final result
    std::cout << _outcome.top() << "\n";
}
