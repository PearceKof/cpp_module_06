/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:28:24 by blaurent          #+#    #+#             */
/*   Updated: 2023/08/08 18:58:56 by blaurent         ###   ########.fr       */
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

#define FLT_MIN -3.40282e+38
#define FLT_MAX 3.40282e+38

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

	static void printChar();
	static void printInt();
	static void printFloat();
	static void printDouble();
	static void setType();
public:
	static void	convert(std::string s);
	static void printResult();
	class InvalidEception : public std::exception
	{
		public:
			virtual const char* what() const throw() { return "Argument invalide"; };
	};
};


#endif