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

	    // Split the line using a comma as the delimiter
	    if (std::getline(ss, date, ',') && (ss >> price))
	        _historicalData[date] = price;
	}
}


void BitcoinExchange::printExchangeDetails(const std::string& date, float value) const
{
    try
    {
        float exchangeRate = getExchangeRate(date, value);
        float result = value * exchangeRate;

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
		this->_historicalData = other._historicalData;
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

int BitcoinExchange::isDateValid(const std::string& date) const
{
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
        return 0; // If not, the date format is invalid
    }

    // Convert the parts to integers using atoi
    int year, month, day;
    year = std::atoi(parts[0].c_str());
    month = std::atoi(parts[1].c_str());
    day = std::atoi(parts[2].c_str());

    // Now, perform date validation checks
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        return 0; // Date components are out of valid ranges
    }

    // Check for months with 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
        {
            return 0; // Invalid day for this month
        }
    }
    else if (month == 2)
    {
        // Check for February (special rules for leap years)
        if ((!isLeapYear(year)) && (day > 28))
        {
            return 0; // February in a non-leap year can have at most 28 days
        }
        else if ((isLeapYear(year)) && (day > 29))
        {
            return 0; // February in a leap year can have at most 29 days
        }
    }

    return 1; // If all conditions are met, the date is valid
}



class NegativeValueException : public std::runtime_error
{
public:
    NegativeValueException() : std::runtime_error("Value is negative.") {}
};

class TooLargeNumberException : public std::runtime_error
{
public:
    TooLargeNumberException() : std::runtime_error("Value is too large.") {}
};

class InexistentDateException : public std::runtime_error
{
public:
    InexistentDateException() : std::runtime_error("Date does not exist.") {}
};

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

    // Check if the date is valid
    if (!isDateValid(date))
    {
        throw std::runtime_error("Error: bad input.");
    }

    // Check if the date exists in the historical data map
    std::map<std::string, float>::const_iterator it = _historicalData.find(date);
    if (it != _historicalData.end())
    {
        // If the date exists in the map, multiply the value by the exchange rate
        float exchangeRate = it->second;
        return exchangeRate; // Corrected order of multiplication
    }
    else
    {
        // Date not found in historical data, find the closest lower date
        std::map<std::string, float>::const_iterator lower = _historicalData.begin();
        for (std::map<std::string, float>::const_iterator iter = _historicalData.begin(); iter != _historicalData.end(); ++iter)
        {
            if (iter->first < date && iter->first > lower->first)
            {
                lower = iter;
            }
        }

        if (lower != _historicalData.end())
        {
            // Use the closest lower date
            float exchangeRate = lower->second;
            return exchangeRate;
        }
        else
        {
            throw std::runtime_error("Error: nonexistent date.");
        }
    }
}
