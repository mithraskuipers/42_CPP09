/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/09 22:25:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/12/29 23:06:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
#include <vector>
#include <string>
#include <cstdlib> // Include the header for atoi
#include <cmath>
#include <cfloat>
#include <limits> // Include for std::numeric_limits
#include <stdexcept> // Include for std::runtime_error
#include <algorithm> // Include for std::max_element
#include <iostream> // cout
#include <fstream>  // ifstream
#include <sstream>  // stringstream
#include <cctype> // For checking types

class BitcoinExchange
{
    public:
        BitcoinExchange(void);
        ~BitcoinExchange(void);
        BitcoinExchange(const std::string& fileBitcoinExchangeRates);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        int isDateValid(const std::string& date) const;
        float getExchangeRate(const std::string& date, float value) const;
        void printAllDetails(const std::string& date, float value) const; // EXTRA
    private:
        std::map<std::string, float>	_exchangeRateData;
};

std::ostream& operator<<(std::ostream& o, const BitcoinExchange& i);

# endif