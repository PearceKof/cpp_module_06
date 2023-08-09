/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:29:31 by blaurent          #+#    #+#             */
/*   Updated: 2023/08/09 14:24:11 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

std::string	ScalarConverter::_str = "";
int			ScalarConverter::_type = 0;

/*
------------------isType functions------------------
*/

bool ScalarConverter::isChar()
{
	if ( _str.length() == 1 && std::isprint( _str[0] ) && !std::isdigit( _str[0] ) )
		return true;
    return false;
}

bool ScalarConverter::isInt()
{
	if ( _str.length() == 0 )
		return false;

    size_t j = 0;
    if ( _str[j] == '-' || _str[j] == '+' )
        j++;

    for ( size_t i( j ) ; i < _str.length() ; i++ )
	{
        if ( !std::isdigit( _str[i] ) )
            return false;
    }
    return true;
}

bool ScalarConverter::isFloat()
{
	if ( _str.find( '.' ) == std::string::npos || _str[_str.length() - 1] != 'f' 
		|| _str.find( '.' ) == 0 || _str.find( '.' ) == _str.length() - 2 )
		return false;

    size_t j = 0;
    if ( _str[j] == '-' || _str[j] == '+' )
        j++;

    int found = 0;
    for ( size_t i( j ) ; i < _str.length() - 1 ; i++ )
	{
        if ( _str[i] == '.' )
            found++;
        if ( ( !std::isdigit( _str[i] ) && _str[i] != '.' && (_str[i] == 'f' && i != _str.length() - 1 )) || found > 1 )
            return false;
    }

    return true;
}

bool ScalarConverter::isDouble()
{
    if ( _str.find( '.' ) == std::string::npos || _str.find( '.' ) == 0 || _str.find( '.' ) == _str.length() - 1 )
        return false;

    size_t j = 0;
    if ( _str[j] == '-' || _str[j] == '+' )
        j++;

    int found = 0;
    for ( size_t i( j ); i <  _str.length(); i++ )
	{
        if ( _str[i] == '.' )
            found++;
        if ( ( !std::isdigit( _str[i] ) && _str[i] != '.' ) || found > 1 )
            return false;
    }

    return true;
}

bool ScalarConverter::isLiteral()
{
	if ( !_str.compare("nan") || !_str.compare("nanf")
        || !_str.compare("+inf") || !_str.compare("+inff")
        || !_str.compare("-inf") || !_str.compare( "-inff" )
        || !_str.compare("-inff") || !_str.compare( "-inff" )
        || !_str.compare("+inff") || !_str.compare( "+inff" ) )
            return true;
    return false;
}

void ScalarConverter::isImpossible()
{
	if ( _str.empty() == true || ( !isChar() && !isInt() && !isFloat() && !isDouble() && !isLiteral() ) )
		throw ScalarConverter::InvalidException();
}


void ScalarConverter::setType()
{
	if ( isChar() )
		_type = CHAR;
	else if ( isInt() )
		_type = INT;
	else if ( isFloat() )
		_type = FLOAT;
	else if ( isDouble() )
		_type = DOUBLE;
	else if ( isLiteral() )
		_type = LITERAL;
	else
		throw ScalarConverter::InvalidException();
}
/*
------------------print functions------------------
*/

void ScalarConverter::printChar(double value)
{
	std::cout << "char: ";

	char c = static_cast<char>(value);
	int overflowChecker = static_cast<int>(value);
    if ( ( overflowChecker > 255 || overflowChecker < 0 ) || _type == LITERAL )
        std::cout << "impossible";
    else if ( !std::isprint( overflowChecker ) )
	{
        std::cout << "Non displayable";
	}
    else
        std::cout << "'" << c << "'";
    std::cout << std::endl;
}

void ScalarConverter::printInt(double value)
{
	std::cout << "int: ";

	double overflowChecker = strtod(_str.c_str(), NULL);
	if (_type == LITERAL || (errno == ERANGE) || overflowChecker < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < overflowChecker)
		std::cout << "impossible";
	else if (_type == CHAR)
		std::cout << static_cast<int>(_str[0]);
	else
		std::cout << static_cast<int>(value);
	std::cout << std::endl;
}

void ScalarConverter::printFloat(double value)
{
	std::cout << "float: ";

	if (!_str.compare("nan") || !_str.compare("nanf") || std::isnan(value))
		std::cout << "nanf" << std::endl;
	else if (!_str.compare("+inff") || !_str.compare("+inf") || ((std::isinf(value) && value > 0) || value > std::numeric_limits<float>::max()))
		std::cout << "+inff" << std::endl;
	else if (!_str.compare( "-inff" ) || !_str.compare("-inf") || (std::isinf(value) && value < 0))
		std::cout << "-inff" << std::endl;
	else
			std::cout <<  std::setprecision(1) << std::fixed << static_cast<float>(value) << "f" << std::endl;
}

void ScalarConverter::printDouble(double value)
{
	std::cout << "double: ";

	if (!_str.compare("nan") || !_str.compare("nanf") || std::isnan(value))
        std::cout << "nan" << std::endl;
    else if (!_str.compare("+inff") || !_str.compare( "+inf") || (std::isinf(value) && value > 0))
        std::cout << "+inf" << std::endl;
    else if (!_str.compare( "-inff" ) || !_str.compare( "-inf" ) || (std::isinf(value) && value < 0))
        std::cout << "-inf" << std::endl;
    else
			std::cout << std::setprecision(1) << std::fixed << value << std::endl;
}

void ScalarConverter::convert(std::string s)
{
	_str = s;
	
	setType();

	double value = 0.0;
	if (_type == CHAR)
		value = static_cast<double>(_str[0]);
	else
		value = strtod(_str.c_str(), NULL);
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);

}