/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:07:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/22 17:20:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
NOTE: THIS CPP09 EX00 IMPLEMENTATION USES:
(1) std::map<std::string, float>
(2) std::list<std::string>
*/

/*
make re ; ./btc input.txt
*/

#include "BitcoinExchange.hpp"

bool isValidDate(const std::string &date)
{
	if (date.length() != 10) // Check if date has exactly 10 characters (YYYY-MM-DD).
		return false;

	for (size_t i = 0; i < date.length(); i++)
	{
		char ch = date[i];
		if (i == 4 || i == 7)
		{
			if (ch != '-')
				return false;
		}
		else if (!std::isdigit(ch))
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./program_name input_file.txt" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::string btcExchangeRatesFile = "data.csv";
	BitcoinExchange exchange(btcExchangeRatesFile);
	std::string line;
	bool firstLine;
	firstLine = true;

	while (std::getline(inputFile, line))
	{
		if (firstLine)
		{
			firstLine = false;
			continue; // Skip the validation for the first line
		}

		// Check if the line follows the specified format
		std::istringstream ss_line(line);
		std::string ss_date;
		float ss_value;
		char separator;

		if (!(ss_line >> ss_date >> separator >> ss_value) || separator != '|' || !isValidDate(ss_date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		try
		{
			float exchangeRate = exchange.getExchangeRate(ss_date, ss_value);
			float result = ss_value * exchangeRate;
			std::cout << ss_date << " => " << ss_value << " = " << result << std::endl;
		}
		catch (const std::exception &error)
		{
			std::cerr << error.what() << std::endl;
		}
	}

	return 0;
}

/*
Notes:
Contents of input.txt have been copied over from the subject.
data.csv has been provided on the project page.
*/
