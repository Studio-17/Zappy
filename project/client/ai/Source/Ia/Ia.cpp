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
    _stop = false;

    _takeMap = {
        {"food", ACTIONS::TAKE_FOOD},
        {"linemate", ACTIONS::TAKE_LINEMATE},
        {"deraumere", ACTIONS::TAKE_DERAUMERE},
        {"sibur", ACTIONS::TAKE_SIBUR},
        {"mendiane", ACTIONS::TAKE_MENDIANE},
        {"phiras", ACTIONS::TAKE_PHIRAS},
        {"thystame", ACTIONS::TAKE_THYSTAME},
    };
    _setMap = {
        {"food", ACTIONS::SET_FOOD},
        {"linemate", ACTIONS::SET_LINEMATE},
        {"deraumere", ACTIONS::SET_DERAUMERE},
        {"sibur", ACTIONS::SET_SIBUR},
        {"mendiane", ACTIONS::SET_MENDIANE},
        {"phiras", ACTIONS::SET_PHIRAS},
        {"thystame", ACTIONS::SET_THYSTAME},
    };

    _inventory = {
        {"food", 0},
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

    _stringElementInMap = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
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
        createMap(_mapSize.second, _mapSize.first);
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
    std::cout << _contentOfMap.size() << std::endl;
}

std::map<std::string, bool> Ia::createTile()
{
    std::map<std::string, bool> tile;

    tile.emplace("player", false);
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
    int nbTilesToFill = 0;

    std::cout << "In fillInTheMap" << std::endl;

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
            setContentTile(content.at(nbTilesToFill), tmpPos.first, tmpPos.second);
            nbTilesToFill++;
            if (first)
                first = false;
        }
    }

    std::cout << "finished fillInTheMap" << std::endl;
}

void Ia::clearContentTile(int x, int y)
{
    _contentOfMap.at(y).at(x).at("food") = false;
    _contentOfMap.at(y).at(x).at("linemate") = false;
    _contentOfMap.at(y).at(x).at("deraumere") = false;
    _contentOfMap.at(y).at(x).at("sibur") = false;
    _contentOfMap.at(y).at(x).at("mendiane") = false;
    _contentOfMap.at(y).at(x).at("phiras") = false;
    _contentOfMap.at(y).at(x).at("thystame") = false;
    _contentOfMap.at(y).at(x).at("player") = false;
}

void Ia::setContentTile(std::vector<std::string> contentOfTile, int x, int y)
{
    std::cout << "In setContentTile" << std::endl;
    clearContentTile(x, y);
    for (auto &resource : contentOfTile)
        if (!resource.empty() && resource[0] != ' ')
            _contentOfMap.at(y).at(x).at(resource) = true;
    std::cout << "finished setContentTile" << std::endl;
}

void Ia::parseLook(std::string response)
{
    std::size_t pos = 0;
    std::string token;
    std::string comaDelimiter = ",";
    std::string spaceDelimiter = " ";
    std::vector<std::string> contentOfTile;
    std::vector<std::vector<std::string>> contentOfMap;

    response = replaceCharacters(response, "[", "");
    response = replaceCharacters(response, " ]", "");

    while ((pos = response.find(comaDelimiter)) != std::string::npos) {
        token = response.substr(0, pos);
        contentOfTile.push_back(token);
        response.erase(0, pos + comaDelimiter.length());
    }
    contentOfTile.push_back(response);

    std::cout << contentOfTile.size() << std::endl;
    for (auto &tile : contentOfTile)
    {
        if (tile[0] == ' ')
            tile.erase(0, 1);
        std::cout << tile << std::endl;
    }

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
    std::vector<std::string> contentOfInventory;
    std::map<std::string, int> inventory;

    response = replaceCharacters(response, "[", "");
    response = replaceCharacters(response, " ]", "");

    std::cout << response << std::endl;

    while ((pos = response.find(comaDelimiter)) != std::string::npos) {
        token = response.substr(1, pos);
        contentOfInventory.push_back(token);
        response.erase(0, pos + comaDelimiter.length());
    }
    for (auto &resource : contentOfInventory) {
        std::size_t pos = resource.find(spaceDelimiter);
        token = resource.substr(0, pos);
        inventory.emplace(token, std::stoi(resource.substr(pos + spaceDelimiter.length())));
    }
    fillInTheInventory(inventory);
}

void Ia::clearTheInventory()
{
    _inventory.at("food") = 0;
    _inventory.at("linemate") = 0;
    _inventory.at("deraumere") = 0;
    _inventory.at("sibur") = 0;
    _inventory.at("mendiane") = 0;
    _inventory.at("phiras") = 0;
    _inventory.at("thystame") = 0;
}

void Ia::fillInTheInventory(std::map<std::string, int> content)
{
    clearTheInventory();
    for (auto &[item, quantity] : content)
        _inventory.at(item) = quantity;
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

std::pair<int, int> Ia::movePlayer(std::pair<int, int> iaPosition)
{
    std::pair<int, int> position;

    position.first = (iaPosition.first + _possibleDirections.at(static_cast<DIRECTION>(_actualIaDirection)).first) % _mapSize.first;
    position.second =(iaPosition.second + _possibleDirections.at(static_cast<DIRECTION>(_actualIaDirection)).second) % _mapSize.second;
    if (position.first < 0)
        position.first += _mapSize.first;
    if (position.second < 0)
        position.second += _mapSize.second;
    iaPosition = position;
    return iaPosition;
    std::cout << "x : " << iaPosition.first << " y : " << iaPosition.second << std::endl;
}

void Ia::changeDirection(DIRECTION direction)
{
    int tmp = static_cast<int>(_actualIaDirection);

    if (direction == DIRECTION::LEFT)
        _actualIaDirection = static_cast<DIRECTION>(tmp - 1 < 0 ? 3 : tmp - 1);
    if (direction == DIRECTION::RIGHT)
        _actualIaDirection = static_cast<DIRECTION>(tmp + 1 > 3 ? 0 : tmp + 1);
}

std::string Ia::getNeededItem()
{
    std::cout << "getNeededItem" << std::endl;
    for (auto &[gemInLevelToObtain, quantity] : _levelsToObtain.at(_actualLevel + 1))
    {
        if (gemInLevelToObtain != "player") {
            if (_inventory.at(gemInLevelToObtain) < quantity)
                return gemInLevelToObtain;
        }
    }
    std::cout << "finish get Needed Item" << std::endl;
    return "elevation";
}

void Ia::forward(std::string const &serverResponse)
{
    std::cout << "Ia::forward" << std::endl;

    if (serverResponse == "ok") {
        _actualIaPosition = movePlayer(_actualIaPosition);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}
void Ia::turnLeft(std::string const &serverResponse)
{
    std::cout << "Ia::turnLeft" << std::endl;

    if (serverResponse == "ok") {
        changeDirection(DIRECTION::LEFT);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::turnRight(std::string const &serverResponse)
{
    std::cout << "Ia::turnRight" << std::endl;

    if (serverResponse == "ok") {
        changeDirection(DIRECTION::RIGHT);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::look(std::string const &serverResponse)
{
    std::cout << "Ia::look" << std::endl;

    parseLook(serverResponse);
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::parseTake(std::string const &resource)
{
    std::cout << "Take : " << resource << std::endl;
    std::cout << "Before Ressource in the map is " << _contentOfMap.at(_actualIaPosition.second).at(_actualIaPosition.first).at(resource) << std::endl;
    _contentOfMap.at(_actualIaPosition.second).at(_actualIaPosition.first).at(resource) = false;
    std::cout << "Now Ressource in the map is " << _contentOfMap.at(_actualIaPosition.second).at(_actualIaPosition.first).at(resource) << std::endl;
    std::cout << "Before nb of it in Inventory : " << _inventory.at(resource) << std::endl;
    _inventory.at(resource)++;
    std::cout << "Now nb of it in Inventory : " << _inventory.at(resource) << std::endl;
}

void Ia::parseSet(std::string const &resource)
{
    std::cout << "Set : " << resource << std::endl;
    std::cout << "Before Ressource in the map is " << _contentOfMap.at(_actualIaPosition.second).at(_actualIaPosition.first).at(resource) << std::endl;
    _contentOfMap.at(_actualIaPosition.second).at(_actualIaPosition.first).at(resource) = true;
    std::cout << "Now Ressource in the map is " << _contentOfMap.at(_actualIaPosition.second).at(_actualIaPosition.first).at(resource) << std::endl;
    std::cout << "Before nb of it in Inventory : " << _inventory.at(resource) << std::endl;
    _inventory.at(resource)--;
    std::cout << "Now nb of it in Inventory : " << _inventory.at(resource) << std::endl;
}

void Ia::inventory(std::string const &serverResponse)
{
    std::cout << "Ia::inventory" << std::endl;
    parseInventory(serverResponse);
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::take(std::string const &serverResponse, std::string resource)
{
    std::cout << "Ia::take" << std::endl;

    if (serverResponse == "ok")
    {
        parseTake(resource);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}

void Ia::set(std::string const &serverResponse, std::string resource)
{
    std::cout << "Ia::set" << std::endl;

    if (serverResponse == "ok")
    {
        parseSet(resource);
    }
    _requestListReceived.pop();
    _requestListSent.pop();
}

// void Ia::elevation(std::string const &serverResponse, std::string resource)
// {

// }

void Ia::handleEvent(ACTIONS action, std::string const &response)
{
    switch (action)
    {
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
    case ACTIONS::TAKE_FOOD:
        take(response, "food");
        break;
    case ACTIONS::SET_FOOD:
        set(response, "food");
        break;
    case ACTIONS::TAKE_LINEMATE:
        take(response, "linemate");
        break;
    case ACTIONS::SET_LINEMATE:
        set(response, "linemate");
        break;
    case ACTIONS::TAKE_DERAUMERE:
        take(response, "deraumere");
        break;
    case ACTIONS::SET_DERAUMERE:
        set(response, "deraumere");
        break;
    case ACTIONS::TAKE_SIBUR:
        take(response, "sibur");
        break;
    case ACTIONS::SET_SIBUR:
        set(response, "sibur");
        break;
    case ACTIONS::TAKE_MENDIANE:
        take(response, "mendiane");
        break;
    case ACTIONS::SET_MENDIANE:
        set(response, "mendiane");
        break;
    case ACTIONS::TAKE_PHIRAS:
        take(response, "phiras");
        break;
    case ACTIONS::SET_PHIRAS:
        set(response, "phiras");
        break;
    case ACTIONS::TAKE_THYSTAME:
        take(response, "thystame");
        break;
    case ACTIONS::SET_THYSTAME:
        set(response, "thystame");
        break;
    default:
        break;
    }
}

void Ia::addActionToQueue(ACTIONS action)
{
    _requestTmp.emplace(action);

    if (_requestListToSend.size() < MAX_ACTION_LIST)
    {
        ACTIONS tmp = _requestTmp.front();
        _requestTmp.pop();
        _requestListToSend.emplace(tmp);
    }
}

void Ia::addMessageToQueue(std::string const &serverResponse)
{
    _requestListReceived.emplace(serverResponse);
}

void Ia::sendResquestServer()
{
    while (!_requestListToSend.empty())
    {
        _client.postRequest(_client.getSocket(), _requestListToSend.front());
        _requestListSent.emplace(_requestListToSend.front());
        _requestListToSend.pop();
    }
}

void Ia::analyzeResponseServer()
{
    std::string message;

    message = _client.getRequest(_client.getSocket());
    if (parseReceiveResponse(message))
    {
        if (!_requestListSent.empty() && !_requestListReceived.empty())
        {
            std::cout << "parseReceivedResponse: " << _requestListReceived.front() << std::endl;
            handleEvent(_requestListSent.front(), _requestListReceived.front());
        }
    }
}

bool Ia::isElementInMap(std::string const &element)
{
    std::cout << "Ia::isElementInMap" << std::endl;
    int x = 0;
    int y = 0;

    for (auto const &map : _contentOfMap)
    {
        x = 0;
        for (auto const &line : map)
        {
            for (auto const &elementInLine : line)
            {
                if (elementInLine.first == element && elementInLine.second == true)
                {
                    _currentTileToGo = {x, y};
                    return true;
                }
            }
            x++;
        }
        y++;
    }
    return false;
}

void Ia::goToTile(int x, int y)
{
    std::cout << "Ia::goToTile x: " << x << " y: " << y << std::endl;
    while (_actualIaPosition.second != y)
    {
        addActionToQueue(ACTIONS::FORWARD);
        sendResquestServer();
        analyzeResponseServer();
    }
    if (_actualIaPosition.first != x || _actualIaPosition.second != y)
    {
        std::cout << "Want to turn" << std::endl;
        if (_actualIaPosition.second < x)
        {
            addActionToQueue(ACTIONS::RIGHT);
            sendResquestServer();
            analyzeResponseServer();
        }
        else
        {
            addActionToQueue(ACTIONS::LEFT);
            sendResquestServer();
            analyzeResponseServer();
        }
        while (_actualIaPosition.first != x)
        {
            addActionToQueue(ACTIONS::FORWARD);
            sendResquestServer();
            analyzeResponseServer();
        }
    }
    std::cout << "IA is in the good tile!" << std::endl;
    emptyTileAndSetGoodElement(x, y);
}

void Ia::searchElement()
{
    std::cout << "Ia::searchElement" << std::endl;
    int x = rand() % 1;
    if (x == 0)
        addActionToQueue(ACTIONS::LEFT);
    else
    {
        addActionToQueue(ACTIONS::RIGHT);
        addActionToQueue(ACTIONS::FORWARD);
    }
}

bool Ia::isTileEmpty(int x, int y)
{
    for (auto &resource : _stringElementInMap)
    {
        if (_contentOfMap.at(y).at(x).at(resource) == true)
            return false;
    }
    return true;
}

bool Ia::isElementInTile(int x, int y, std::string element)
{
    if (_contentOfMap.at(y).at(x).at(element) == true)
        return true;
    return false;
}

void Ia::emptyTileAndSetGoodElement(int x, int y)
{
    std::cout << "Ia::emptyTileAndSetGoodElement" << std::endl;
    while (!isTileEmpty(x, y))
    {
        std::cout << "isTileEmpty" << std::endl;
        for (auto &resource : _stringElementInMap)
        {
            std::cout << "resources: " << resource << std::endl;
            if (isElementInTile(x, y, resource))
            {
                addActionToQueue(ACTIONS::LOOK);
                addActionToQueue(_takeMap.at(resource));
                sendResquestServer();
                analyzeResponseServer();
                std::cout << "EmptyTileAndSetGoodElement: Took " << resource << std::endl;
            }
        }
    }
    std::cout << "FINISHED TO CLEAR THE MAP" << std::endl;
    // addActionToQueue(ACTIONS::SET_LINEMATE);
    // sendResquestServer();
    // analyzeResponseServer();
}

void Ia::mainLoop()
{
    srand(time(NULL));
    addActionToQueue(ACTIONS::INVENTORY);
    addActionToQueue(ACTIONS::LOOK);

    while (!_isDead)
    {
        // add action to queue here
        sendResquestServer();
        analyzeResponseServer();
        std::string neededElement = getNeededItem();
        std::cout << "neededElement: " << neededElement << std::endl;
        if (neededElement != "elevation")
        {
            std::cout << "getNeededItem" << std::endl;
            if (_requestListSent.empty())
            {
                std::cout << "Queue size ->" << _requestListSent.size() << std::endl;
                // attendre que le serveur nous renvoie toutes les reponses
                if (isElementInMap(neededElement))
                {
                    goToTile(_currentTileToGo.first, _currentTileToGo.second);
                    std::cout << "Finished to go to tile" << std::endl;
                }
                else
                {
                    addActionToQueue(ACTIONS::LOOK);
                    searchElement();
                }
            }
        }
    }
}
