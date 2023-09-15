// RPN.hpp
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPNCalculator {
public:
    RPNCalculator();
    int evaluate(const std::string& expression);

private:
    std::stack<int> operandStack;
    bool isOperator(const std::string& token);
    int performOperation(const std::string& op);
};

#endif // RPN_HPP
