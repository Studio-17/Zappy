/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** OptionsErrors
*/

#include "OptionsErrors.hpp"

OptionsErrors::OptionsErrors(std::string const &message) : Errors("Options: " + message)
{
}

OptionsErrors::~OptionsErrors()
{
}
