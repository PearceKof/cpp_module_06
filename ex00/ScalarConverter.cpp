/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:29:31 by blaurent          #+#    #+#             */
/*   Updated: 2023/07/11 16:26:48 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

std::string	ScalarConverter::_str = "";
char		ScalarConverter::_c = 0;
int			ScalarConverter::_i = 0;
float		ScalarConverter::_f = 0;
double		ScalarConverter::_d = 0;
int			ScalarConverter::_type = 0;
bool		ScalarConverter::_isValid = true;

/*
------------------isType functions------------------
*/

bool ScalarConverter::isChar()
{
    return _str.length() == 1 && std::isalpha( _str[0] ) && std::isprint( _str[0] );
}

bool ScalarConverter::isInt()
{
    int j = 0;
    if ( _str[j] == '-' || _str[j] == '+' )
        j++;
    for ( int i( j ); i < ( int ) _str.length(); i++ )
	{
        if ( !std::isdigit( _str[i] ) )
            return false;
    }
    return true;
}

bool ScalarConverter::isFloat()
{
    if ( _str.find( '.' ) == std::string::npos || _str.back() != 'f' 
        || _str.find( '.' ) == 0 || _str.find( '.' ) == _str.length() - 2 )
        return false;
    int found = 0;
    int j = 0;
    if ( _str[j] == '-' || _str[j] == '+' )
        j++;
    for ( int i( j ); i < ( int ) _str.length() - 1; i++ ) {
        if ( _str[i] == '.' )
            found++;
        if ( ( !std::isdigit( _str[i] ) && _str[i] != '.' ) || found > 1 )
            return false;
    }

    return true;
}

bool ScalarConverter::isDouble()
{
    if ( _str.find( '.' ) == std::string::npos || _str.find( '.' ) == 0 
        || _str.find( '.' ) == _str.length() - 1 )
        return false;
    int j = 0;
    int found = 0;
    if ( _str[j] == '-' || _str[j] == '+' )
        j++;
    for ( int i( j ); i < ( int ) _str.length(); i++ )
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
	if ( !_isValid || !_str.compare("nan") || !_str.compare("nanf")
        || !_str.compare("+inf") || !_str.compare("+inff")
        || !_str.compare("-inf") || !_str.compare( "-inff" )
        || !_str.compare("-inff") || !_str.compare( "-inff" )
        || !_str.compare("+inff") || !_str.compare( "+inff" ))
            return true;
    return false;
}

bool ScalarConverter::isImpossible()
{
	try
	{
		if ( _type == INT )
			_i = std::stoi( _str );
		else if ( _type == FLOAT )
			_f = std::stof( _str );
		else if ( _type == DOUBLE )
			_d = std::stod( _str );
	}
	catch (std::exception& e)
	{
		_isValid = false;
		return true;
	}
	return false;
}


void ScalarConverter::setType()
{
	if (isChar())
		_type = CHAR;
	else if (isInt())
		_type = INT;
	else if (isFloat())
		_type = FLOAT;
	else if (isDouble())
		_type = DOUBLE;
	else if (isLiteral())
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
    if ((_i > 127 || _i < 0) || !_isValid || _type == LITERAL)
        std::cout << "impossible";
    else if (!std::isprint(_i))
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
	if (!_isValid || _type == LITERAL)
		std::cout << "impossible";
	else
		std::cout << _i;
	std::cout << std::endl;
}

void ScalarConverter::printFloat()
{
	std::cout << "float: ";
	if (!_str.compare("nan") || !_str.compare("nanf"))
		std::cout << "nanf";
	else if (!_str.compare("+inff") || !_str.compare("+inf"))
		std::cout << "+inff";
	else if (!_str.compare( "-inff" ) || !_str.compare("-inf"))
		std::cout << "-inff";
	else if (!_isValid)
		std::cout << "impossible";
	else
	{
        if (_f - static_cast< int > ( _f ) == 0 )
			std::cout << _f << ".0f";
		else
			std::cout << _f << "f";
	}
	std::cout << std::endl;
}

void ScalarConverter::printDouble()
{
	std::cout << "double: ";
    if (!_str.compare("nan") || !_str.compare("nanf"))
        std::cout << "nan";
    else if (!_str.compare("+inff") || !_str.compare( "+inf"))
        std::cout << "+inf";
    else if (!_str.compare( "-inff" ) || !_str.compare( "-inf" ))
        std::cout << "-inf";
    else if (!_isValid)
        std::cout << "impossible";
    else
	{
        if (_d - static_cast<int>(_d) == 0)
            std::cout << _d << ".0";
        else
            std::cout << _d;
    }
	std::cout << std::endl;
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
	if (isImpossible())
		return;
	switch (_type)
	{
	case CHAR:
		_c = _str[0];
		_i = static_cast< int >(_c);
		_f = static_cast< float >(_c);
		_d = static_cast< double >(_c);
		break;
	case INT:
		_i = std::stoi(_str);
		_f = static_cast< float >(_i);
		_d = static_cast< double >(_i);
		_c = static_cast< char >(_i);
		break;
	case FLOAT:
		_f = std::stof(_str);
		_i = static_cast< int >(_f);
		_d = static_cast< double >(_f);
		_c = static_cast< char >(_f);
		break;
	case DOUBLE:
		_d = std::stod(_str);
		_i = static_cast< int >(_d);
		_f = static_cast< float >(_d);
		_c = static_cast< char >(_d);
		break;
	default:
		break;
	}
	
}