/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** ClientErrors
*/

#include "ClientErrors.hpp"

ClientErrors::ClientErrors(std::string const &message) : Errors("Options: " + message)
{
}

ClientErrors::~ClientErrors()
{
}
