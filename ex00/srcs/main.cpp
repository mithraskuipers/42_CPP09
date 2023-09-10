#include "BitcoinExchange.hpp"
#include <iostream> //cout
#include <fstream> //ifstrem
#include <sstream> //stringstream

bool checkExtension(const std::string& s, const std::string& suffix)
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

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input.txt" << std::endl;
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

	std::getline(inputFile, line); // to skip header row of input.txt
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
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }

    return 0;
}
