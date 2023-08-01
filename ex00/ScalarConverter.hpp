/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:28:24 by blaurent          #+#    #+#             */
/*   Updated: 2023/08/01 17:37:05 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>
# include <iostream>
# include <cstdlib>
# include <cctype>
# include <limits>

enum{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	LITERAL,
	VOID
};

class ScalarConverter
{
private:
	static std::string	_str;
	static char			_c;
	static int			_i;
	static float		_f;
	static double		_d;
	static int			_type;
	static bool			_isValid;

	ScalarConverter();
	ScalarConverter(const ScalarConverter& src);

	static bool isChar();
	static bool isInt();
	static bool isFloat();
	static bool isDouble();
	static bool isLiteral();
	static bool isImpossible();

	static void printChar();
	static void printInt();
	static void printFloat();
	static void printDouble();
	static void setType();
public:
	~ScalarConverter();
	ScalarConverter&	operator=(const ScalarConverter& src);
	static void	convert(std::string s);
	static void printResult();

	class OverflowEception : public std::exception
	{
		public:
			virtual const char* what() const throw() { return "Overflow"; };
	};
	class InvalidEception : public std::exception
	{
		public:
			virtual const char* what() const throw() { return "Argument invalide"; };
	};
};


#endif