/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   BitcoinExchange.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/09 22:25:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/09/09 22:28:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>


class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(const std::string& fileHistorialData);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		
	private:
	
};

std::ostream& operator<<(std::ostream& o, const BitcoinExchange& i);


# endif
