/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:28:24 by blaurent          #+#    #+#             */
/*   Updated: 2023/08/09 14:12:13 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>
# include <cmath>
# include <iostream>
# include <cstdlib>
# include <cctype>
# include <limits>
# include <iomanip>
# include <cerrno>

enum{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	LITERAL
};

class ScalarConverter
{
private:
	static std::string	_str;
	static int			_type;

	ScalarConverter();
	ScalarConverter(const ScalarConverter& src);
	ScalarConverter&	operator=(const ScalarConverter& src);
	~ScalarConverter();

	static bool isChar();
	static bool isInt();
	static bool isFloat();
	static bool isDouble();
	static bool isLiteral();
	static void isImpossible();

	static void printChar(double value);
	static void printInt(double value);
	static void printFloat(double value);
	static void printDouble(double value);
	static void setType();
public:
	static void	convert(std::string s);
	class InvalidException : public std::exception
	{
		public:
			virtual const char* what() const throw() { return "Argument invalide"; };
	};
};


#endif