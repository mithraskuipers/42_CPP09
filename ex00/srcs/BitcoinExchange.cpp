/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 17:07:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/26 19:24:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	return ;
}

BitcoinExchange::BitcoinExchange(const std::string& fileBitcoinExchangeRates)
{
	std::ifstream	dataCsvFile(fileBitcoinExchangeRates.c_str());				// Open data.csv file
	if (!dataCsvFile.good())													// If data.csv not exists or can't be opened.
	{
		throw std::runtime_error("Error: could not open data.csv file.");
	}
	if (!dataCsvFile.is_open())													// If data.csv is not opened
	{
		throw std::runtime_error("Error: could not open data.csv file.");
	}
	std::string		dataCsvLine;
	while (std::getline(dataCsvFile, dataCsvLine))
	{
		std::stringstream	ss_line(dataCsvLine);
		std::string			ss_date;
		float				ss_price;

		if (std::getline(ss_line, ss_date, ',') && (ss_line >> ss_price))		// Split line into tokens on basis of ','. Take first float token and put in ss_price.
		{
			this->_historicalData[ss_date] = ss_price;							// Mapping between strings and floating point values
		}
	}
}

void BitcoinExchange::printAllDetails(const std::string& date, float value) const
{
	try
	{
		float	exchangeRate = this->getExchangeRate(date, value);
		float	result = value * exchangeRate;

		std::cout << "Date: " << date << std::endl;
		std::cout << "Bitcoin Value: " << value << std::endl;
		std::cout << "Exchange Rate: " << exchangeRate << std::endl;
		std::cout << "Result: " << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
	return ;
}

BitcoinExchange::~BitcoinExchange(void)
{
	return ;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->_historicalData = other._historicalData;
	}
	return (*this);
}

int isLeapYear(int year)														// Required because leap years have extra day in February
{
	// Check 1: Check if the year is a potential candidate for being a leap year
	if (year % 4 == 0)
	{
		// Check 2: Check if the year is divisible by 100
		// Years that are divisible by 100 are not leap years unless they are also divisible by 400
		if (year % 100 != 0)
		{
			return (1);															// Leap year
		}
		else
		{
			// Check 3: Check if the year is divisible by 400
			if (year % 400 == 0)
			{
				return (1);														// Leap year
			}
			else
			{
				return (0);														// Not a leap year
			}
		}
	}
	else
	{
		return (0);																// Not a leap year
	}
}

int BitcoinExchange::isDateValid(const std::string& date) const
{
	std::vector<std::string>	date_vector;
	std::istringstream			iss_date(date);
	std::string					date_part;
	
	while (std::getline(iss_date, date_part, '-'))								// Split the input string on '-'

	{
		date_vector.push_back(date_part);
	}

	if (date_vector.size() != 3)												// Check if there are exactly 3 parts (year, month, day)
	{
		return (0);																// If not, the date format is invalid
	}

	// Convert the parts to integers using atoi
	int	year = std::atoi(date_vector[0].c_str());
	int	month = std::atoi(date_vector[1].c_str());
	int	day = std::atoi(date_vector[2].c_str());

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)				// Check date unit ranges
	{
		return (0);
	}

	if (month == 4 || month == 6 || month == 9 || month == 11)					// Check for months with 30 days
	{
		if (day > 30)
		{
			return (0);
		}
	}
	else if (month == 2)														// Exception case for February
	{
		if ((!isLeapYear(year)) && (day > 28))									// If not leap year February can have at most 28 days
		{
			return (0);
		}
		else if ((isLeapYear(year)) && (day > 29))								// If leap year February can have at most 29 days
		{
			return (0);
		}
	}
	return 1;																	// If all conditions are met, the date is valid
}

float BitcoinExchange::getExchangeRate(const std::string& date, float value) const
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

	if (!isDateValid(date))														// Check if the date is valid

	{
		throw std::runtime_error("Error: bad input.");
	}

	std::map<std::string, float>::const_iterator it = _historicalData.find(date);	// Check if the date exists in the historical data map

	if (it != _historicalData.end())
	{
		float exchangeRate = it->second;										// If the date exists in the map, multiply the value by the exchange rate

		return (exchangeRate);													// Corrected order of multiplication
	}
	else
	{
		std::map<std::string, float>::const_iterator lower = _historicalData.begin();	// Date not found in historical data, find the closest lower date

		for (std::map<std::string, float>::const_iterator iter = _historicalData.begin(); iter != _historicalData.end(); ++iter)
		{
			if (iter->first < date && iter->first > lower->first)
			{
				lower = iter;
			}
		}

		if (lower != _historicalData.end())
		{
			float exchangeRate = lower->second;									// Use the closest lower date

			return (exchangeRate);
		}
		else
		{
			throw std::runtime_error("Error: nonexistent date.");
		}
	}
}

/*
Exceptions
*/

class NegativeValueException : public std::runtime_error
{
	public:
		NegativeValueException() : std::runtime_error("Value is negative.")
		{
			
		}
};

class TooLargeNumberException : public std::runtime_error
{
	public:
		TooLargeNumberException() : std::runtime_error("Value is too large.")
		{
			
		}
};

class InexistentDateException : public std::runtime_error
{
	public:
		InexistentDateException() : std::runtime_error("Date does not exist.")
		{
			
		}
};
