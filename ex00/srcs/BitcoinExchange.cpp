#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	return ;
}

BitcoinExchange::BitcoinExchange(const std::string& fileHistorialData)
{
	std::ifstream file(fileHistorialData.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("Error: could not open the historical data file.");
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date;
		float price;
		// Extract a date (delimited by ',') from stringstream
		// Read float (price) from the remaining content of stringstream.
		// If both operations succeed, update the _historicalData map.
		if (std::getline(ss, date, ',') && (ss >> price))
			_historicalData[date] = price;
		std::cout << _historicalData[date] << std::endl;
		
	}	
	return ;
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
		this->_historicalData = other._historicalData;
	return (*this);
}


int BitcoinExchange::isDateValid(const std::string& date)
{
	// split string on '-'
	// if there are no 3 parts, throw error
	// if there are 3 parts, treat them as year/month/day in variables
	// now various date checks, 
	// like year cant be lower than 0, 
	// month lower than 1, month not higher than 12, 
	// day not smaller than 1, not greater than 31


	// Split the input string on '-'
	std::vector<std::string> parts;
	std::istringstream iss(date);
	std::string part;
	
	while (std::getline(iss, part, '-'))
	{
		parts.push_back(part);
	}

	// Check if there are exactly 3 parts (year, month, day)
	if (parts.size() != 3)
	{
		return false; // If not, the date format is invalid
	}

	// Convert the parts to integers using atoi
	int year, month, day;
	year = std::atoi(parts[0].c_str());
	month = std::atoi(parts[1].c_str());
	day = std::atoi(parts[2].c_str());

	// Now, perform date validation checks
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		return false; // Date components are out of valid ranges
	}

	// Check for months with 30 days
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			return false; // Invalid day for this month
		}
	}
	// Check for February (special rules for leap years)
	else if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		
		if (isLeapYear && day > 29)
		{
			return false; // February in a leap year can have at most 29 days
		}
		else if (!isLeapYear && day > 28)
		{
			return false; // February in a non-leap year can have at most 28 days
		}
	}
	return true; // If all conditions are met, the date is valid
}
