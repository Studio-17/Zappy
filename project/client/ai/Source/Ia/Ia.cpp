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
    _actualIaPosition = {0, 0};
    _possibleDirections = {
        {DIRECTION::UP, {0, -1}},
        {DIRECTION::RIGHT, {1, 0}},
        {DIRECTION::DOWN, {0, 1}},
        {DIRECTION::LEFT, {-1, 0}},
    };
    _rowDirections = {
        {DIRECTION::UP, {1, 0}},
        {DIRECTION::RIGHT, {0, 1}},
        {DIRECTION::DOWN, {-1, 0}},
        {DIRECTION::LEFT, {0, -1}},
    };
    _actualIaDirection = DIRECTION::DOWN;
    _actualLevel = 1;
    _isDead = false;

    _inventory = {
        {"food", 10},
        {"linemate", 0},
        {"deraumere", 0},
        {"sibur", 0},
        {"mendiane", 0},
        {"phiras", 0},
        {"thystame", 0}
    };

    _levelsToObtain = {
        {2,
            {{"food", 0},
            {"linemate", 1},
            {"deraumere", 0},
            {"sibur", 0},
            {"mendiane", 0},
            {"phiras", 0},
            {"thystame", 0},
            {"player", 1},}
        },
        {3,
            {{"food", 0},
            {"linemate", 1},
            {"deraumere", 1},
            {"sibur", 1},
            {"mendiane", 0},
            {"phiras", 0},
            {"thystame", 0},
            {"player", 2},}
        },
        {4,
            {{"food", 0},
            {"linemate", 2},
            {"deraumere", 0},
            {"sibur", 1},
            {"mendiane", 0},
            {"phiras", 2},
            {"thystame", 0},
            {"player", 2},}
        },
        {5,
            {{"food", 0},
            {"linemate", 1},
            {"deraumere", 1},
            {"sibur", 2},
            {"mendiane", 0},
            {"phiras", 1},
            {"thystame", 0},
            {"player", 4},}
        },
        {6,
            {{"food", 0},
            {"linemate", 1},
            {"deraumere", 2},
            {"sibur", 1},
            {"mendiane", 3},
            {"phiras", 0},
            {"thystame", 0},
            {"player", 4},}
        },
        {7,
            {{"food", 0},
            {"linemate", 1},
            {"deraumere", 2},
            {"sibur", 3},
            {"mendiane", 0},
            {"phiras", 1},
            {"thystame", 0},
            {"player", 6},}
        },
        {8,
            {{"food", 0},
            {"linemate", 2},
            {"deraumere", 2},
            {"sibur", 2},
            {"mendiane", 2},
            {"phiras", 2},
            {"thystame", 1},
            {"player", 6},}
        }
    };
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
    } catch (ClientErrors const &ClientError) {
        std::cerr << ClientError.what() << std::endl;
    }
    mainLoop();
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

bool Ia::parseReceiveResponse(std::string message)
{
    std::size_t pos = 0;
    std::string backline = "\n";
    std::string serverResponse;

    _bufferServerResponse += message;
    if ((pos = _bufferServerResponse.find(backline)) != std::string::npos) {
       serverResponse = _bufferServerResponse.substr(0, pos);
       _bufferServerResponse.erase(0, pos + backline.length());
       addMessageToQueue(serverResponse);
       return true;
    }
    return false;
}

void Ia::fillInTheMap(std::vector<std::vector<std::string>> content, std::pair<int, int> playerPosition, DIRECTION direction)
{
    std::pair<int, int> playerOrientation = _possibleDirections.at(direction);
    std::pair<int, int> rowOrientation = _rowDirections.at(direction);
    int nbTiles = 0;

    for (int i = 0; i <= _actualLevel; i++)
        nbTiles += 1 + (i * 2);
    bool first = true;
    for (int i = 0; i <= _actualLevel; i++) {
        for (int index = -i; index <= i; index++) {
            std::pair<int, int> tmpPos;
            tmpPos.first = playerPosition.first;
            tmpPos.first += playerOrientation.first * i;
            tmpPos.first += rowOrientation.first * index;
            if (tmpPos.first >= _mapSize.first)
                tmpPos.first = 0;
            else if (tmpPos.first < 0)
                tmpPos.first = _mapSize.first - 1;
            tmpPos.second = playerPosition.second;
            tmpPos.second += playerOrientation.second * i;
            tmpPos.second += rowOrientation.second * index;
            if (tmpPos.second >= _mapSize.second)
                tmpPos.second = 0;
            else if (tmpPos.second < 0)
                tmpPos.second = _mapSize.second - 1;
            setContentTile(content, tmpPos.first, tmpPos.second);
            if (first)
                first = false;
        }
    }
}

void Ia::setContentTile(std::vector<std::vector<std::string>> contentOfTile, int x, int y)
{
    for (auto &line : contentOfTile) {
        for (auto &tile : line) {
            if (tile == "food")
                _contentOfMap.at(y).at(x).at("food") = true;
            else if (tile == "linemate")
                _contentOfMap.at(y).at(x).at("linemate") = true;
            else if (tile == "deraumere")
                _contentOfMap.at(y).at(x).at("deraumere") = true;
            else if (tile == "sibur")
                _contentOfMap.at(y).at(x).at("sibur") = true;
            else if (tile == "mendiane")
                _contentOfMap.at(y).at(x).at("mendiane") = true;
            else if (tile == "phiras")
                _contentOfMap.at(y).at(x).at("phiras") = true;
            else if (tile == "thystame")
                _contentOfMap.at(y).at(x).at("thystame") = true;
        }
    }
}

void Ia::parseLook(std::string response)
{
    std::size_t pos = 0;
    std::string token;
    std::string comaDelimiter = ",";
    std::string spaceDelimiter = " ";
    std::vector<std::string> contentOfTile;
    std::vector<std::vector<std::string>> contentOfMap;

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
    fillInTheMap(contentOfMap, _actualIaPosition, _actualIaDirection);
}

void Ia::parseInventory(std::string response)
{
    std::size_t pos = 0;
    std::string token;
    std::string comaDelimiter = ",";
    std::string spaceDelimiter = " ";
    std::map<std::string, int> contentOfInventory;

    while ((pos = response.find(comaDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        response.erase(0, pos + comaDelimiter.length());
        pos = token.find(spaceDelimiter);
        std::string key = token.substr(0, pos);
        int value = std::stoi(token.substr(pos + spaceDelimiter.length()));
        contentOfInventory.emplace(key, value);
    }
    fillInTheInventory(contentOfInventory);
}

void Ia::fillInTheInventory(std::map<std::string, int> content)
{
    for (auto &item : content) {
        if (item.first == "food")
            _inventory.at("food") = item.second;
        else if (item.first == "linemate")
            _inventory.at("linemate") = item.second;
        else if (item.first == "deraumere")
            _inventory.at("deraumere") = item.second;
        else if (item.first == "sibur")
            _inventory.at("sibur") = item.second;
        else if (item.first == "mendiane")
            _inventory.at("mendiane") = item.second;
        else if (item.first == "phiras")
            _inventory.at("phiras") = item.second;
        else if (item.first == "thystame")
            _inventory.at("thystame") = item.second;
    }
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

// std::vector<ACTIONS> Ia::moveToTile(int tile)
// {
//     std::vector<ACTIONS> actions;
//     int centeredTile;
//     bool isInGoodFloor = false;

//     for (int floor = 0; !isInGoodFloor; floor++) {
//         centeredTile = getCenteredTile(floor);
//         if (tile >= centeredTile + floor && tile <= centeredTile + floor)
//             isInGoodFloor = true;
//         else
//             actions.push_back(ACTIONS::FORWARD);
//     }
//     while (centeredTile != tile) {
//         if (centeredTile > tile)
//             actions.push_back(ACTIONS::LEFT);
//         else
//             actions.push_back(ACTIONS::RIGHT);
//     }
//     return actions;
// }

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

// bool Ia::searchGem(std::string const &gem)
// {
//     for (auto &[gemInLevelToObtain, quantity] : _levelsToObtain.at(_actualLevel))
//         if (_inventory.at(gem) <= quantity)
//             return true;
//     return false;
// }

// bool Ia::wantToTakeAnyObject(std::vector<std::map<std::string, bool>> objectsPerTile)
// {
//     int index = 0;

//     for (auto &objectsInTile : objectsPerTile) {
//         for (auto &[gem, status] : objectsInTile) {
//             if (status == true && searchGem(gem)) {
//                 _objectToTake = {index, gem};
//                 return true;
//             }
//         }
//         index++;
//     }
//     return false;
// }

bool Ia::isBracketsInString(std::string str)
{
    if (str.find("[ ") != std::string::npos && str.find(" ]") != std::string::npos && str.find("\n") != std::string::npos && str.find("[ ") < str.find(" ]"))
        return true;
    return false;
}

void Ia::forward(std::string const &serverResponse)
{
    if (serverResponse == "ok") {
        movePlayer();
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}
void Ia::turnLeft(std::string const &serverResponse)
{
    if (serverResponse == "ok") {
        changeDirection(DIRECTION::LEFT);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::turnRight(std::string const &serverResponse)
{
    if (serverResponse == "ok") {
        changeDirection(DIRECTION::RIGHT);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::look(std::string const &serverResponse)
{
    std::cout << "Look response->" << serverResponse << std::endl;
    // if (isBracketsInString(serverResponse)) {
        // parseLook(serverResponse);
    // }
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::inventory(std::string const &serverResponse)
{
    std::cout << "Inventory response->" << serverResponse << std::endl;
    // if (isBracketsInString(serverResponse)) {
    //     parseInventory(serverResponse);
    //     _requestListReceived.pop();
    //     _requestListSent.pop();
    // }
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
            inventory(response);
            break;
        default:
            break;
    }
}

void Ia::addActionToQueue(ACTIONS action)
{
    _requestTmp.emplace(action);

    if (_requestListToSend.size() < MAX_ACTION_LIST) {
        ACTIONS tmp = _requestTmp.front();
        _requestTmp.pop();
        _requestListToSend.emplace(tmp);
    }
}

void Ia::addMessageToQueue(std::string const &serverResponse)
{
    _requestListReceived.emplace(serverResponse);
}

void Ia::mainLoop()
{
    std::string message;

    while (!_isDead) {
        if (!_requestListToSend.empty()) {
            _client.postRequest(_client.getSocket(), _requestListToSend.front());
            _requestListSent.emplace(_requestListToSend.front());
            _requestListToSend.pop();
        }

        // add action to queue here

        message = _client.getRequest(_client.getSocket());
        if (parseReceiveResponse(message)) {
            if (!_requestListSent.empty() && !_requestListReceived.empty())
                handleEvent(_requestListSent.front(), _requestListReceived.front());
        }
    }
}
