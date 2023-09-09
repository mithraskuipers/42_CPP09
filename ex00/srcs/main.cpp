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

int main(int argc, char** argv)
{
	if (argc != 2)																// Check parameters
	{
		std::cerr << "Usage: " << argv[0] << " <input.txt>" << std::endl;
		return (1);
	}
	if (checkExtension(argv[1], ".txt"))										// Check parameter extension
	{
		std::cerr << "Error. Make sure <input.txt> has the .txt extension" << std::endl;
		return (1);	
	}
	std::ifstream fileDateValues(argv[1]);										// Open second parameter file
	if (!fileDateValues.is_open())
	{
		std::cerr << "Error: could not open input file" << std::endl;
		return (1);
	}
	std::string	line;															// 
	std::getline(fileDateValues, line);
	BitcoinExchange test("data.csv");
	while(std::getline(fileDateValues, line))
	{
		(void)line;
		//std::cout << line << std::endl;

	}
}