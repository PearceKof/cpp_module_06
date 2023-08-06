/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:49:11 by blaurent          #+#    #+#             */
/*   Updated: 2023/08/06 18:37:58 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP
# include <stdint.h>
# include "Data.hpp"

class Serializer
{
private:
	Serializer();
	Serializer(const Serializer&);
	operator=(const Serializer&);
public:
	~Serializer();
	static Data* deserialize(uintptr_t data);
	static uintptr_t serialize(Data* ptr);
};

#endif