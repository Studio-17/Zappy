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
        {ACTIONS::FORWARD, "Forward\n"},
        {ACTIONS::RIGHT, "Right\n"},
        {ACTIONS::LEFT, "Left\n"},
        {ACTIONS::LOOK, "Look\n"},
        {ACTIONS::INVENTORY, "Inventory\n"},
        {ACTIONS::BROADCAST_TEXT, "Broadcast text\n"},
        {ACTIONS::CONNECT_NBR, "Connect_nbr\n"},
        {ACTIONS::FORK, "Fork\n"},
        {ACTIONS::EJECT, "Eject\n"},
        {ACTIONS::INCANTATION, "Incantation\n"},
    };

    _levelsToObtain = {
        {2,
            {
                {"food", 0},
                {"linemate", 1},
                {"deraumere", 0},
                {"sibur", 0},
                {"mendiane", 0},
                {"phiras", 0},
                {"thystame", 0},
                {"player", 1},
            }
        },
        {3,
            {
                {"food", 0},
                {"linemate", 1},
                {"deraumere", 1},
                {"sibur", 1},
                {"mendiane", 0},
                {"phiras", 0},
                {"thystame", 0},
                {"player", 2},
            }
        },
        {4,
            {
                {"food", 0},
                {"linemate", 2},
                {"deraumere", 0},
                {"sibur", 1},
                {"mendiane", 0},
                {"phiras", 2},
                {"thystame", 0},
                {"player", 2},
            }
        },
        {5,
            {
                {"food", 0},
                {"linemate", 1},
                {"deraumere", 1},
                {"sibur", 2},
                {"mendiane", 0},
                {"phiras", 1},
                {"thystame", 0},
                {"player", 4},
            }
        },
        {6,
            {
                {"food", 0},
                {"linemate", 1},
                {"deraumere", 2},
                {"sibur", 1},
                {"mendiane", 3},
                {"phiras", 0},
                {"thystame", 0},
                {"player", 4},
            }
        },
        {7,
            {
                {"food", 0},
                {"linemate", 1},
                {"deraumere", 2},
                {"sibur", 3},
                {"mendiane", 0},
                {"phiras", 1},
                {"thystame", 0},
                {"player", 6},
            }
        },
        {8,
            {
                {"food", 0},
                {"linemate", 2},
                {"deraumere", 2},
                {"sibur", 2},
                {"mendiane", 2},
                {"phiras", 2},
                {"thystame", 1},
                {"player", 6},
            }
        }
    };

    _actualLevel = 1;
}

Ia::~Ia()
{
}

std::vector<std::map<std::string, bool>> Ia::parseLook(std::string response)
{
    size_t pos = 0;
    std::string token;
    std::string comaDelimiter = ",";
    std::string spaceDelimiter = " ";
    std::vector<std::string> contentOfTile;
    std::vector<std::map<std::string, bool>> contentOfMap;
    std::map<std::string, bool> contentOfTileMap = {
        {"food", false},
        {"linemate", false},
        {"deraumere", false},
        {"sibur", false},
        {"mendiane", false},
        {"phiras", false},
        {"thystame", false},
        {"player", false},
    };

    response.erase(remove(response.begin(), response.end(), '['), response.end());
    response.erase(remove(response.begin(), response.end(), ']'), response.end());

    while ((pos = response.find(comaDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        contentOfTile.push_back(token);
        response.erase(0, pos + comaDelimiter.length());
    }
    for (std::size_t index = 0; index < contentOfTile.size(); index ++) {
        std::vector<std::string> tmp;
        while ((pos = contentOfTile.at(index).find(spaceDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        tmp.push_back(token);
        response.erase(0, pos + comaDelimiter.length());
        }
        std::map<std::string, bool> tmpContentMap = contentOfTileMap;
        for (auto &resource : tmp) {
            if (tmpContentMap.find(resource) != tmpContentMap.end()) {
                tmpContentMap[resource] = true;
            }
        }
        contentOfMap.push_back(tmpContentMap);
    }

    return contentOfMap;
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

std::string replaceCharacters(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;

    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string Ia::transformRessourceToAction(std::string object)
{
    object[0] = std::toupper(object[0]);
    return object;
}

std::vector<Ia::ACTIONS> Ia::moveToTile(int tile)
{
    std::vector<Ia::ACTIONS> actions;
    int centeredTile;
    bool isInGoodFloor = false;

    for (int floor = 0; !isInGoodFloor; floor++) {
        centeredTile = getCenteredTile(floor);
        if (tile >= centeredTile + floor && tile <= centeredTile + floor)
            isInGoodFloor = true;
        else
            actions.push_back(ACTIONS::FORWARD);
    }
    while (centeredTile != tile) {
        if (centeredTile > tile)
            actions.push_back(ACTIONS::LEFT);
        else
            actions.push_back(ACTIONS::RIGHT);
    }
    return actions;
}

bool Ia::searchGem(std::string const &gem)
{
    for (auto &[gemInLevelToObtain, quantity] : _levelsToObtain.at(_actualLevel))
        if (_inventory.at(gem) <= quantity)
            return true;
    return false;
}

bool Ia::wantToTakeAnyObject(std::vector<std::map<std::string, bool>> objectsPerTile)
{
    int index = 0;

    for (auto &objectsInTile : objectsPerTile) {
        for (auto &[gem, status] : objectsInTile) {
            if (status == true && searchGem(gem)) {
                _objectToTake = {index, gem};
                return true;
            }
        }
        index++;
    }
    return false;
}


// 1- Le but est de look et si un objet l'intéresse il se déplace jusqu'à la case et prend l'objet
// 2- Si aucun objet l'intéresse alors elle tourne left / right et refait la ligne 1
// 3- Si rien ne l'intérresse alors q'elle a tourné sur elle même 3 fois dans le meme sens alors elle s'avance d'une case et reviens au 1
// 4- Si sur la case + dans son inventory elle a tout ce qu'il faut pour faire incantation alors elle lance l'incantation
// 5- elle recupere tout les objets sur la case et les met dans son inventaire
// 6- elle demande au serveur 'inventory' et si tout et bon elle pose les objetcs qu'il faut et fait l'incantation
void Ia::mainLoop()
{
    std::string response;
    std::string object;
    std::vector<std::map<std::string, bool>> allObjInTile;

    while (true) {
        sleep(1);
        response = _client.handleAction(doAction(Ia::ACTIONS::LOOK));
        allObjInTile = parseLook(response);
        if (wantToTakeAnyObject(allObjInTile)) {
            moveToTile(_objectToTake.first);
            std::cout << "move to tile" << std::endl;
            // takeObject()
        } else
            response = _client.handleAction(doAction(Ia::ACTIONS::LEFT));
        // response = _client.handleAction(doAction(ACTIONS::FORWARD));
        // if (response.compare("ok"))
        //     std::cout << "IA received: " << response << std::endl;
        // else
        //     std::cout << "Bad response from the IA: " << response << std::endl;
    }
}
