/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:15:21 by blaurent          #+#    #+#             */
/*   Updated: 2023/07/11 16:48:55 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data *data = new Data;

    data->str = "achraf";
    data->nb = 30;

    std::cout << "test str: " << Serializer::deserialize( Serializer::serialize( data ) )->str << std::endl;
    std::cout << "test nb: " << Serializer::deserialize( Serializer::serialize( data ) )->nb << std::endl;

    delete data;

    return 0;
}