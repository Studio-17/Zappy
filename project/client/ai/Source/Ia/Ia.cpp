/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ia
*/

#include <unistd.h>

#include "Ia.hpp"

Ia::Ia() : _client()
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
    mainLoop();
}

void Ia::mainLoop()
{
    std::string response;

    while (true) {
        usleep(1);
        response = _client.handleAction("Forward");
        if (response == "ok")
            std::cout << "IA received: " << response<< std::endl;
        else
            std::cout << "Bad response from the IA: " << response << std::endl;
    }
}
