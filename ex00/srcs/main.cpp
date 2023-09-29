/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:07:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/29 13:25:58 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// Check if file extension equals specified suffix
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
	if ((argc != 2) || (checkExtension(argv[1], ".txt")))
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);											// input.txt (multiplictation table).
	if (!inputFile.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange	exchange("data.csv");										// btc exchange rates.
	std::string		line;

	std::getline(inputFile, line);												// Trick to skip the header row of input.txt.

	while (std::getline(inputFile, line))										// Process each line in the input file.
	{
		std::istringstream	ss_line(line);										// Turn input line into string stream (to split it up in tokens).
		std::string			ss_date;
		float				ss_value;

		if (std::getline(ss_line, ss_date, '|') && (ss_line >> ss_value))		// Split line into tokens on basis of '|'. Extract first token (i.e. date info) in date. Take first float token and put in ss_value.
		{
			size_t first = ss_date.find_first_not_of(" \t\n\r\f\v");			// Find index of first non-ws character.

			size_t last = ss_date.find_last_not_of(" \t\n\r\f\v");				// Find index of last non-ws character.

			ss_date = ss_date.substr(first, (last - first) + 1);				// Extract only date itself. +1 to account for last character.

			try
			{
				float exchangeRate = exchange.getExchangeRate(ss_date, ss_value);	// Get exchange rate for a given date and ss_value. Value error checking.
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
