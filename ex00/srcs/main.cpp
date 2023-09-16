#include "BitcoinExchange.hpp"
#include <iostream> // cout
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits> // Include for std::numeric_limits

int checkExtension(const std::string& s, const std::string& suffix)
{
    if (s.length() >= suffix.length())
    {
        std::string sSuffix = s.substr(s.length() - suffix.length());
        if (sSuffix.compare(suffix) == 0)
        {
            return (0);
        }
    }
    return (1);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        // std::cerr << "Usage: " << argv[0] << " input.txt" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange exchange("data.csv");
    std::string line;

    std::getline(inputFile, line); // to skip the header row of input.txt
    // Process each line in the input file
    while (std::getline(inputFile, line))
    {
        // Split the line at the '|' character
        std::istringstream ss(line);
        std::string date;
        float value;

        if (std::getline(ss, date, '|') && (ss >> value))
        {
            // Trim leading and trailing whitespace from date
            size_t first = date.find_first_not_of(" \t\n\r\f\v");
            size_t last = date.find_last_not_of(" \t\n\r\f\v");
            if (first != std::string::npos && last != std::string::npos)
            {
                date = date.substr(first, last - first + 1);
            }

            try
            {
                float exchangeRate = exchange.getExchangeRate(date, value);
                float result = value * exchangeRate;
                std::cout << date << " => " << value << " = " << result << std::endl;
                // EXTRA FOR DEBUGGING! Shows date, Bitcoin value, exchange rate, and multiplication result
                // std::cout << std::endl;
                // exchange.printExchangeDetails(date, value);
                // std::cout << std::endl;
            }
            catch (const std::exception& error)
            {
                std::cerr << error.what() << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
    return 0;
}

/*
Notes:
Contents of input.txt have been copied over from the subject.
data.csv has been provided on the project page.
*/
