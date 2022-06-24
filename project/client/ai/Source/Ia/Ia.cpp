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
    _actualIaPosition = {0, 0};
    _possibleDirections = {
        {DIRECTION::UP, {0, -1}},
        {DIRECTION::RIGHT, {1, 0}},
        {DIRECTION::DOWN, {0, 1}},
        {DIRECTION::LEFT, {-1, 0}},
    };
    _actualIaDirection = DIRECTION::DOWN;
    _actualLevel = 1;

    _actionCommands = {
        {ACTION::FORWARD, "Forward\n"},
        {ACTION::RIGHT, "Right\n"},
        {ACTION::LEFT, "Left\n"},
        {ACTION::LOOK, "Look\n"},
        {ACTION::INVENTORY, "Inventory\n"},
        {ACTION::BROADCAST_TEXT, "Broadcast text\n"},
        {ACTION::CONNECT_NBR, "Connect_nbr\n"},
        {ACTION::FORK, "Fork\n"},
        {ACTION::EJECT, "Eject\n"},
        {ACTION::INCANTATION, "Incantation\n"},
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
}

Ia::~Ia()
{
}

void Ia::createMap(int mapHeight, int mapWidth)
{
    std::vector<std::map<std::string, bool>> tmp;

    for (int line = 0; line < mapWidth; line++) {
        for (int col = 0; col < mapHeight; col++)
            tmp.emplace_back(createTile());
        _contentOfMap.emplace_back(tmp);
        tmp.clear();
    }
}

std::map<std::string, bool> Ia::createTile()
{
    std::map<std::string, bool> tile;
    tile.emplace("food", false);
    tile.emplace("linemate", false);
    tile.emplace("deraumere", false);
    tile.emplace("sibur", false);
    tile.emplace("mendiane", false);
    tile.emplace("phiras", false);
    tile.emplace("thystame", false);
    return tile;
}

void Ia::fillInTheMap(std::vector<std::vector<std::string>> content, std::pair<int, int> position, std::pair<int, int> direction)
{
    std::cout << "Not filled yet" << std::endl;
}

void Ia::parseLook(std::string response)
{
    size_t pos = 0;
    std::string token;
    std::string comaDelimiter = ",";
    std::string spaceDelimiter = " ";
    std::vector<std::string> contentOfTile;
    std::vector<std::vector<std::string>> contentOfMap;
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

    response = replaceCharacters(response, "[ ", "");
    response = replaceCharacters(response, " ]", "");

    while ((pos = response.find(comaDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        contentOfTile.push_back(token);
        response.erase(0, pos + comaDelimiter.length());
    }
    contentOfTile.push_back(response);

    for (std::size_t index = 0; index < contentOfTile.size(); index ++) {
        contentOfMap.push_back({});
        std::string tmp = contentOfTile.at(index);
        while ((pos = tmp.find(spaceDelimiter)) != std::string::npos) {
            token = tmp.substr(0, pos);
            contentOfMap.at(index).push_back(token);
            tmp.erase(0, pos + spaceDelimiter.length());
        }
        contentOfMap.at(index).push_back(tmp);
    }
    // fillInTheMap(contentOfMap, _actualIaPosition, _actualIaDirection);
}

void Ia::startIa()
{
    try {
        _client.setup();
        _client.connection();
        _mapSize = _client.getMapSize();
        createMap(_mapSize.first, _mapSize.second);
    } catch (ClientErrors const &ClientError) {
        std::cerr << ClientError.what() << std::endl;
    }
    mainLoop();
}

std::string Ia::replaceCharacters(std::string str, const std::string& from, const std::string& to)
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

std::vector<Ia::ACTION> Ia::moveToTile(int tile)
{
    std::vector<Ia::ACTION> actions;
    int centeredTile;
    bool isInGoodFloor = false;

    for (int floor = 0; !isInGoodFloor; floor++) {
        centeredTile = getCenteredTile(floor);
        if (tile >= centeredTile + floor && tile <= centeredTile + floor)
            isInGoodFloor = true;
        else
            actions.push_back(ACTION::FORWARD);
    }
    while (centeredTile != tile) {
        if (centeredTile > tile)
            actions.push_back(ACTION::LEFT);
        else
            actions.push_back(ACTION::RIGHT);
    }
    return actions;
}

void Ia::movePlayer()
{
    std::pair<int, int> position;

    position.first = (_actualIaPosition.first + _possibleDirections.at(static_cast<DIRECTION>(_actualIaDirection)).first) % _mapSize.first;
    position.second =(_actualIaPosition.second + _possibleDirections.at(static_cast<DIRECTION>(_actualIaDirection)).second) % _mapSize.second;
    if (position.first < 0)
        position.first += _mapSize.first;
    if (position.second < 0)
        position.second += _mapSize.second;
    _actualIaPosition = position;
}

void Ia::changeDirection(DIRECTION direction)
{
    int tmp = static_cast<int>(_actualIaDirection);

    if (direction == DIRECTION::LEFT)
        _actualIaDirection = static_cast<DIRECTION>(tmp - 1 < 0 ? 3 : tmp - 1);
    if (direction == DIRECTION::RIGHT)
        _actualIaDirection = static_cast<DIRECTION>(tmp + 1 > 3 ? 0 : tmp + 1);
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

void Ia::mainLoop()
{
    std::string response;
    std::string object;
    std::vector<std::map<std::string, bool>> allObjInTile;

    while (true) {
        sleep(1);
        response = _client.handleAction(doAction(Ia::ACTION::LOOK));
        std::cout << "Response: " << response << std::endl;
        movePlayer();
        changeDirection(DIRECTION::RIGHT);
        // parseLook("[ sibur mendiane,, linemate, food ]");
        std::cout << "Position: " << _actualIaPosition.first << " " << _actualIaPosition.second << std::endl;
        std::cout << "Direction: " << _possibleDirections.at(_actualIaDirection).first << " " << _possibleDirections.at(_actualIaDirection).second << std::endl;
    }
}
