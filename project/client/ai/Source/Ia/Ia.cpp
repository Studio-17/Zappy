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
    _actionCommands = {
        {ACTIONS::FORWARD, "Forward"},
        {ACTIONS::RIGHT, "Right"},
        {ACTIONS::LEFT, "Left"},
        {ACTIONS::LOOK, "Look"},
        {ACTIONS::INVENTORY, "Inventory"},
        {ACTIONS::BROADCAST_TEXT, "Broadcast text"},
        {ACTIONS::CONNECT_NBR, "Connect_nbr"},
        {ACTIONS::FORK, "Fork"},
        {ACTIONS::EJECT, "Eject"},
        {ACTIONS::INCANTATION, "Incantation"},
    };
    _objectCommands = {
        {OBJECTS::FOOD, "Food"},
        {OBJECTS::LINEMATE, "Linemate"},
        {OBJECTS::DERAUMERE, "Deraumate"},
        {OBJECTS::SIBUR, "Sibur"},
        {OBJECTS::MENDIANE, "Mendiane"},
        {OBJECTS::PHIRAS, "Phiras"},
        {OBJECTS::THYSTAME, "Thystame"},
    };
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

std::string Ia::takeObject(OBJECTS object)
{
    return ("Take " + _objectCommands.at(object) + "\n");
}

std::string Ia::setObject(OBJECTS object)
{
    return ("Set " + _objectCommands.at(object) + "\n");
}

std::string Ia::doAction(ACTIONS action)
{
    return (_actionCommands.at(action) + "\n");
}

std::string replaceCharacters(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;

    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string Ia::transformObjectToAction(std::string object)
{
    object[0] = std::toupper(object[0]);
    return object;
}

std::vector<std::vector<std::string>> Ia::parseLook(std::string response)
{
    size_t pos = 0;
    std::string token;
    std::string comaDelimiter = ",";
    std::string spaceDelimiter = " ";
    std::vector<std::string> tileContent;
    std::vector<std::vector<std::string>> tilesContent;

    response.erase(remove(response.begin(), response.end(), '['), response.end());
    response.erase(remove(response.begin(), response.end(), ']'), response.end());

    while ((pos = response.find(comaDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        tileContent.push_back(token);
        response.erase(0, pos + comaDelimiter.length());
    }
    for (std::size_t index = 0; index < tileContent.size(); index ++) {
        while ((pos = tileContent.at(index).find(spaceDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        tilesContent.at(index).push_back(token);
        response.erase(0, pos + comaDelimiter.length());
        }
    }
    return tilesContent;
}

std::vector<Ia::ACTIONS> Ia::moveToTile(int tile, OBJECTS object)
{

}

Ia::OBJECTS Ia::wantToTakeAnObject(std::string response)
{

}

// 1- Le but est de look et si un objet l'interesse il se déplace jusqu'a la case et prend l'objet
// 2- Si aucun objet l'intéresse alors elle tourne left / right et refait la ligne 1
// 3- Si rien ne l'interresse alorsd q'elle a tourné sur elle meme (donc 3 fois left ou 3 fois right) alors elle s'avance d'une case et reviens au 1
void Ia::mainLoop()
{
    std::string response;

    while (true) {
        sleep(1);
        response = _client.handleAction(doAction(ACTIONS::FORWARD));
        if (response.compare("ok"))
            std::cout << "IA received: " << response << std::endl;
        else
            std::cout << "Bad response from the IA: " << response << std::endl;
    }
}
