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
	return ;
}