// main.cpp
#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <RPN expression>" << std::endl;
        return 1;
    }

    std::string expression = argv[1];
    RPNCalculator calculator;
    int result = calculator.evaluate(expression);
    std::cout << result << std::endl;

    return 0;
}
