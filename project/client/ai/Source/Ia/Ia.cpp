/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ia
*/

#include <unistd.h>

#include "Ia.hpp"

const int MAX_ACTION_LIST = 10;

Ia::Ia() : _client()
{
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
    _isDead = false;
}

Ia::~Ia()
{
}

void Ia::startIa()
{
    try {
        _client.setup();
        _client.connection();
        _mapSize = _client.getMapSize();
        _inventory = _client.getInvetory();
    } catch (ClientErrors const &ClientError) {
        std::cerr << ClientError.what() << std::endl;
    }
    mainLoop();
}

std::vector<std::map<std::string, bool>> Ia::parseLook(std::string response)
{
    std::size_t pos = 0;
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

std::vector<ACTIONS> Ia::moveToTile(int tile)
{
    std::vector<ACTIONS> actions;
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

void Ia::forward(std::string const &serverResponse)
{
    if (serverResponse == "ok\n") {
        _requestListReceived.pop();
        _requestListSent.pop();
    }
}
void Ia::turnLeft(std::string const &serverResponse)
{
    if (serverResponse == "ok\n") {
        _requestListReceived.pop();
        _requestListSent.pop();
    }
}
void Ia::turnRight(std::string const &serverResponse)
{
    if (serverResponse == "ok\n") {
        _requestListReceived.pop();
        _requestListSent.pop();
    }
}
void Ia::look(std::string const &serverResponse)
{
}

void Ia::handleEvent(ACTIONS action, std::string const &response)
{
    switch (action) {
        case ACTIONS::FORWARD:
            forward(response);
            break;
        case ACTIONS::LEFT:
            turnLeft(response);
            break;
        case ACTIONS::RIGHT:
            turnRight(response);
            break;
        case ACTIONS::LOOK:
            look(response);
            break;
        case ACTIONS::INVENTORY:
            break;
        default:
            break;
    }
}

void Ia::addActionToQueu(ACTIONS action)
{
    _requestListToSend.emplace(action);

    if (_requestListSent.size() < MAX_ACTION_LIST) {
        ACTIONS tmp = _requestListToSend.front();
        _requestListToSend.pop();
        _requestListSent.emplace(tmp);
    }
}

void Ia::addMessageToQueu(std::string const &serverResponse)
{
    _requestListReceived.emplace(serverResponse);
}

void Ia::mainLoop()
{
    std::string message;

    while (!_isDead) {
        sleep(1);
        handleEvent(_requestListSent.front(), _requestListReceived.front());

        // add action to queu here

        message = _client.getRequest(_client.getSocket());
        addMessageToQueu(message);
    }
}
