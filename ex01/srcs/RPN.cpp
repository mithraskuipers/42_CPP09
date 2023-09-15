// RPN.cpp
#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib> // Include the cstdlib header

RPNCalculator::RPNCalculator() {}

bool RPNCalculator::isOperator(const std::string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPNCalculator::performOperation(const std::string& op) {
    int operand2 = operandStack.top();
    operandStack.pop();
    int operand1 = operandStack.top();
    operandStack.pop();

    if (op == "+")
        return operand1 + operand2;
    else if (op == "-")
        return operand1 - operand2;
    else if (op == "*")
        return operand1 * operand2;
    else if (op == "/") {
        if (operand2 == 0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            std::exit(1); // Use std::exit instead of exit
        }
        return operand1 / operand2;
    }

    return 0; // Invalid operator
}

int RPNCalculator::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (!isOperator(token)) {
            int operand;
            std::istringstream(token) >> operand;
            operandStack.push(operand);
        } else {
            if (operandStack.size() < 2) {
                std::cerr << "Error: Insufficient operands for operator " << token << std::endl;
                std::exit(1); // Use std::exit instead of exit
            }
            int result = performOperation(token);
            operandStack.push(result);
        }
    }

    if (operandStack.size() == 1)
        return operandStack.top();
    else {
        std::cerr << "Error: Invalid expression" << std::endl;
        std::exit(1); // Use std::exit instead of exit
    }
}
