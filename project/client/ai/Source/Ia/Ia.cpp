/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ia
*/

#include "Ia.hpp"

Ia::Ia(int test) : _client()
{
}

Ia::~Ia()
{
}

void Ia::setUpOptions(int ac, char **av)
{
    _client.setupOptions(ac, av);
}

void Ia::handleOptions()
{
    _client.handleOptions();
}

void Ia::startIa()
{
    try {
        _client.setup();
        _client.connection();
        _mapSize = _client.getMapSize();
    } catch (ClientErrors const &ClientError) {
        std::cerr << ClientError.what() << std::endl;
    }
}
