/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:07:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/12/29 23:06:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
NOTE: THIS CPP09 EX00 IMPLEMENTATION USES:
(1) std::map<std::string, float>
(2) std::vector<std::string>
*/

#include "BitcoinExchange.hpp"

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

bool isValidDate(const std::string& date)
{
    for (size_t i = 0; i < date.length(); ++i)
    {
        char ch = date[i];
        if (!std::isdigit(ch) && ch != '-')
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    if ((argc != 2) || (checkExtension(argv[1], ".txt")))
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]); // input.txt (multiplication table).
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange exchange("data.csv"); // btc exchange rates.
    std::string line;

    std::getline(inputFile, line); // Trick to skip the header row of input.txt.

    while (std::getline(inputFile, line)) // Process each line in the input file.
    {
        std::istringstream ss_line(line); // Turn input line into a string stream (to split it up into tokens).
        std::string ss_date;
        float ss_value;

        if (std::getline(ss_line, ss_date, '|') && (ss_line >> ss_value))
        {
            size_t first = ss_date.find_first_not_of(" \t\n\r\f\v"); // Find the index of the first non-ws character.
            size_t last = ss_date.find_last_not_of(" \t\n\r\f\v"); // Find the index of the last non-ws character.
            ss_date = ss_date.substr(first, (last - first) + 1); // Extract only the date itself. +1 to account for the last character.

            if (isValidDate(ss_date)) // Check if the date contains only numbers or '-'
            {
                try
                {
                    float exchangeRate = exchange.getExchangeRate(ss_date, ss_value); // Get the exchange rate for a given date and ss_value. Value error checking.
                    float result = ss_value * exchangeRate;
                    std::cout << ss_date << " => " << ss_value << " = " << result << std::endl;

                    // EXTRA FOR DEBUGGING! Shows date, Bitcoin ss_value, exchange rate, and multiplication result
                    // std::cout << std::endl;
                    // exchange.printAllDetails(ss_date, ss_value);
                    // std::cout << std::endl;
                }
                catch (const std::exception& error)
                {
                    std::cerr << error.what() << std::endl;
                }
            }
            else
            {
                std::cerr << "Error: Invalid date format => " << ss_date << std::endl;
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
