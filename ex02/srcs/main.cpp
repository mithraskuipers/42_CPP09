#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "PmergeMe.hpp"
#include <algorithm>


int main(int argc, char* argv[]) {
    // Parse command-line arguments and store them in a vector and a list.
    std::vector<int> vectorInput;
    std::list<int> listInput;

    for (int i = 1; i < argc; ++i) {
        int num = std::atoi(argv[i]);
        if (num != 0 || (num == 0 && argv[i][0] == '0')) {
            vectorInput.push_back(num);
            listInput.push_back(num);
        } else {
            std::cerr << "Error: Invalid input" << std::endl;
            return 1;
        }
    }

    // Display the unsorted sequences.
    std::cout << "Vector Before:";
    printContainer(vectorInput);

    std::cout << "List Before:";
    printContainer(listInput);

    // Start timing for the vector.
    clock_t vectorStartTime = clock();

    // Sort the vector using the Ford-Johnson algorithm.
    fordJohnsonSort(vectorInput);

    // End timing for the vector.
    clock_t vectorEndTime = clock();
    double vectorElapsedTime = static_cast<double>(vectorEndTime - vectorStartTime) / CLOCKS_PER_SEC * 1e6; // Microseconds

    // Start timing for the list.
    clock_t listStartTime = clock();

    // Sort the list using the Ford-Johnson algorithm.
    fordJohnsonSort(listInput);

    // End timing for the list.
    clock_t listEndTime = clock();
    double listElapsedTime = static_cast<double>(listEndTime - listStartTime) / CLOCKS_PER_SEC * 1e6; // Microseconds

    // Display the sorted sequences.
    std::cout << "Vector After:";
    printContainer(vectorInput);

    std::cout << "List After:";
    printContainer(listInput);

    // Display the time taken by each container to sort the sequence.
    std::cout << "Time to process a range of " << argc - 1 << " elements with vector: " << std::fixed << std::setprecision(5) << vectorElapsedTime << " us" << std::endl;
    std::cout << "Time to process a range of " << argc - 1 << " elements with list: " << std::fixed << std::setprecision(5) << listElapsedTime << " us" << std::endl;

    return 0;
}
