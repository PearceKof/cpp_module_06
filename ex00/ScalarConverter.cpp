/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:29:31 by blaurent          #+#    #+#             */
/*   Updated: 2023/08/08 18:58:49 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

std::string	ScalarConverter::_str = "";
char		ScalarConverter::_c = 0;
int			ScalarConverter::_i = 0;
float		ScalarConverter::_f = 0;
double		ScalarConverter::_d = 0;
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
    if ( _str.find( '.' ) == std::string::npos || _str.find( '.' ) == 0 
        || _str.find( '.' ) == _str.length() - 1 )
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
		throw ScalarConverter::InvalidEception();
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
		_type = VOID;
}
/*
------------------print functions------------------
*/

void ScalarConverter::printChar()
{
	std::cout << "char: ";

    if ( ( _i > 255 || _i < 0 ) || _type == LITERAL )
        std::cout << "impossible";
    else if ( !std::isprint( _i ) )
	{
        std::cout << "Non displayable";
	}
    else
        std::cout << "'" << _c << "'";
    std::cout << std::endl;
}

void ScalarConverter::printInt()
{
	std::cout << "int: ";
	double overflowChecker = strtod(_str.c_str(), NULL);
	if ((errno == ERANGE) || overflowChecker < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < overflowChecker)
		std::cout << "impossible";
	else
		std::cout << _i;
	std::cout << std::endl;
}

void ScalarConverter::printFloat()
{
	std::cout << "float: ";

	if (!_str.compare("nan") || !_str.compare("nanf"))
		std::cout << "nanf" << std::endl;
	else if (!_str.compare("+inff") || !_str.compare("+inf"))
		std::cout << "+inff" << std::endl;
	else if (!_str.compare( "-inff" ) || !_str.compare("-inf"))
		std::cout << "-inff" << std::endl;
	else
	{
		double overflowChecker = strtod(_str.c_str(), NULL);
		if ((errno == ERANGE && (overflowChecker == -HUGE_VAL || overflowChecker == HUGE_VAL)) || (overflowChecker < FLT_MIN || overflowChecker > FLT_MAX))
			std::cout << "impossible" << std::endl;
		else
			std::cout <<  std::setprecision(1) << std::fixed << _f << "f" << " versus " << static_cast<float>(overflowChecker) << std::endl;
	}
}

void ScalarConverter::printDouble()
{
	std::cout << "double: ";

    if (!_str.compare("nan") || !_str.compare("nanf"))
        std::cout << "nan" << std::endl;
    else if (!_str.compare("+inff") || !_str.compare( "+inf"))
        std::cout << "+inf" << std::endl;
    else if (!_str.compare( "-inff" ) || !_str.compare( "-inf" ))
        std::cout << "-inf" << std::endl;
    else
	{
		double overflowChecker = strtod(_str.c_str(), NULL);
		if (errno == ERANGE && (overflowChecker == -HUGE_VAL || overflowChecker == HUGE_VAL))
			std::cout << "impossible" << std::endl;
		else
			std::cout << std::setprecision(1) << std::fixed << _d << " versus " << static_cast<double>(overflowChecker) << std::endl;
    }
}

void ScalarConverter::printResult()
{
	printChar();
	printInt();
	printFloat();
	printDouble();
}

void ScalarConverter::convert(std::string s)
{
	_str = s;
	setType();

	isImpossible();
	switch ( _type )
	{
	case CHAR:
		// std::cout << "is a char" << std::endl;
		_c = _str[0];
		_i = static_cast< int >(_c);
		_f = static_cast< float >(_c);
		_d = static_cast< double >(_c);
		break;
	case INT:
		// std::cout << "is a int" << std::endl;
		_i = static_cast<int>(std::strtod(_str.c_str(), NULL));
		_f = static_cast< float >(_i);
		_d = static_cast< double >(_i);
		_c = static_cast< char >(_i);
		break;
	case FLOAT:
		// std::cout << "is a float" << std::endl;
		_f = static_cast<float>(std::strtod(_str.c_str(), NULL));
		_i = static_cast< int >(_f);
		_d = static_cast< double >(_f);
		_c = static_cast< char >(_f);
		break;
	case DOUBLE:
		// std::cout << "is a double" << std::endl;
		_d = static_cast< double >(std::strtod(_str.c_str(), NULL));
		_i = static_cast< int >(_d);
		_f = static_cast< float >(_d);
		_c = static_cast< char >(_d);
		break;
	}
	
}