/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:07:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2024/02/22 17:02:28 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	return;
}

BitcoinExchange::BitcoinExchange(const std::string &fileBitcoinExchangeRates)
{
	std::ifstream dataCsvFile(fileBitcoinExchangeRates.c_str()); // Open data.csv file
	if (!dataCsvFile.good())									 // If data.csv not exists or can't be opened.
	{
		throw std::runtime_error("Error: could not open data.csv file.");
	}
	if (!dataCsvFile.is_open()) // If data.csv is not opened
	{
		throw std::runtime_error("Error: could not open data.csv file.");
	}
	std::string dataCsvLine;
	while (std::getline(dataCsvFile, dataCsvLine))
	{
		std::stringstream ss_line(dataCsvLine);
		std::string ss_date;
		float ss_price;

		if (std::getline(ss_line, ss_date, ',') && (ss_line >> ss_price)) // Split line into tokens on basis of ','. Take first float token and put in ss_price.
		{
			this->_exchangeRateData[ss_date] = ss_price; // Mapping between strings and floating point values
		}
	}
}

void BitcoinExchange::printAllDetails(const std::string &date, float value) const
{
	try
	{
		float exchangeRate = this->getExchangeRate(date, value);
		float result = value * exchangeRate;

		std::cout << "Date: " << date << std::endl;
		std::cout << "Bitcoin Value: " << value << std::endl;
		std::cout << "Exchange Rate: " << exchangeRate << std::endl;
		std::cout << "Result: " << result << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
	return;
}

BitcoinExchange::~BitcoinExchange(void)
{
	return;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_exchangeRateData = other._exchangeRateData;
	}
	return (*this);
}

int isLeapYear(int year) // Required because leap years have extra day in February
{
	// Check 1: Check if the year is a potential candidate for being a leap year
	if (year % 4 == 0)
	{
		// Check 2: Check if the year is divisible by 100
		// Years that are divisible by 100 are not leap years unless they are also divisible by 400
		if (year % 100 != 0)
		{
			return (1); // Leap year
		}
		else
		{
			// Check 3: Check if the year is divisible by 400
			if (year % 400 == 0)
			{
				return (1); // Leap year
			}
			else
			{
				return (0); // Not a leap year
			}
		}
	}
	else
	{
		return (0); // Not a leap year
	}
}

#include <list> // Include the list header
int BitcoinExchange::isDateValid(const std::string &date) const
{
	std::list<std::string> date_list;
	std::istringstream iss_date(date);
	std::string date_part;

	while (std::getline(iss_date, date_part, '-')) // Split the input string on '-'
	{
		date_list.push_back(date_part); // Push each part into the list
	}

	if (date_list.size() != 3) // Check if there are exactly 3 parts (year, month, day)
	{
		return 0; // If not, the date format is invalid
	}

	// Convert the parts to integers using atoi
	int year = std::atoi(date_list.front().c_str());
	date_list.pop_front(); // Remove the year from the list
	int month = std::atoi(date_list.front().c_str());
	date_list.pop_front(); // Remove the month from the list
	int day = std::atoi(date_list.front().c_str());

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) // Check date unit ranges
	{
		return 0;
	}

	if (month == 4 || month == 6 || month == 9 || month == 11) // Check for months with 30 days
	{
		if (day > 30)
		{
			return 0;
		}
	}
	else if (month == 2) // Exception case for February
	{
		if ((!isLeapYear(year)) && (day > 28)) // If not leap year February can have at most 28 days
		{
			return 0;
		}
		else if ((isLeapYear(year)) && (day > 29)) // If leap year February can have at most 29 days
		{
			return 0;
		}
	}
	return 1; // If all conditions are met, the date is valid
}

float BitcoinExchange::getExchangeRate(const std::string &date, float value) const
{
	// Check if the value is too large or too small for both float and int
	if (value < -FLT_MAX || value > FLT_MAX || value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
	{
		throw std::runtime_error("Error: too large a number.");
	}

	if (value > 1000)
	{
		throw std::runtime_error("Error: too large a number.");
	}

	if (value < 0)
	{
		throw std::runtime_error("Error: not a positive number.");
	}

	if (!isDateValid(date)) // Check if the date is valid

	{
		throw std::runtime_error("Error: bad input.");
	}

	std::map<std::string, float>::const_iterator it = _exchangeRateData.find(date); // Check if the date exists in the historical data map and get the date and exchange rate.

	if (it != _exchangeRateData.end()) // If iterator exists (not equal to end of map)..
	{
		float exchangeRate = it->second; // Take the historical data (second ; value from key-value pairs) from the iterator

		return (exchangeRate); // Corrected order of multiplication
	}

	// Find the closest lower date in the historical data map
	std::map<std::string, float>::const_iterator lower = _exchangeRateData.begin();
	std::map<std::string, float>::const_iterator iter;

	for (iter = _exchangeRateData.begin(); iter != _exchangeRateData.end(); ++iter)
	{
		if ((iter->first < date) && (iter->first > lower->first)) // Date is lower than input date, but higher than previously found lower date
		{
			lower = iter; // Update the closest lower date
		}
	}

	if (lower != _exchangeRateData.end()) // If a lower date is found, return its exchange rate
	{
		float exchangeRate = lower->second;
		return (exchangeRate);
	}
	else // If no lower date is found, throw an error
	{
		throw std::runtime_error("Error: nonexistent date.");
	}
}
