/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Errors
*/

#include "Errors.hpp"

Errors::Errors(std::string const &message) throw() : _message(message)
{
}

Errors::~Errors() throw()
{
}

const char *Errors::what() const throw()
{
	return _message.c_str();
}
