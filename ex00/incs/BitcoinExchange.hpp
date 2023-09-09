/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/09 22:25:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/09 23:12:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib> // Include the header for atoi

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		BitcoinExchange(const std::string& fileHistorialData);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		int isDateValid(const std::string& date);
	private:
    	std::map<std::string, float>	_historicalData;
};

std::ostream& operator<<(std::ostream& o, const BitcoinExchange& i);


# endif
