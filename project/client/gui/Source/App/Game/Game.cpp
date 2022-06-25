/*
** EPITECH PROJECT, 2022
** project
** File description:
** Game
*/

#include <ctime>
#include "Game.hpp"

static std::vector<std::pair<COMMANDS_GUI, void(Game::*)(char *)>> _commandsMap = {
    std::make_pair(PLAYER_CONNECTED, &Game::handleAddPlayer),
    std::make_pair(PLAYER_POSITION, &Game::handleUpdatePlayerPosition),
    std::make_pair(PLAYER_ORIENTATION, &Game::handleUpdatePlayerOrientation),
    std::make_pair(PLAYER_LEVEL, &Game::handleUpdatePlayerLevel),
    std::make_pair(PLAYER_INVENTORY, &Game::handleUpdatePlayerInventory),
    std::make_pair(CONTENT_TILE, &Game::handleUpdateContentTile),
    std::make_pair(CONTENT_MAP, &Game::handleUpdateContentMap)
};

Game::Game(std::shared_ptr<Client> client, std::shared_ptr<RayLib::CinematicCamera> camera) : _tilesModel("Resources/Tiles/wall_side.obj"), _playersModel("Resources/Players/player.iqm"), _tilesTexture("Resources/Tiles/wall_side.png"), _playersAnimation("Resources/Players/player.iqm", 1), AScene()
{
    std::srand(std::time(nullptr));
    _playersTextures.emplace_back("Resources/Players/cyan.png");
    loadResourcesModels();
    _client = client;
    _camera = camera;

    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(500, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(700, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(900, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(1100, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(1300, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(1500, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "0", Position(1700, 1000, 0)));

    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Apple:", Position(410, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Linemate:", Position(590, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Deraumere:", Position(780, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Sibur:", Position(1010, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Mendiane:", Position(1190, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Phiras:", Position(1410, 1000, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Thystame:", Position(1590, 1000, 0)));

    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Server disconnected", Position(1600, 20, 0)));

    for (auto &text : _texts)
        text->setColor(WHITE);

    _images.push_back(std::make_unique<Object::Image>("Resources/Images/background_sky.png", Position(0, 0)));
    _images.push_back(std::make_unique<Object::Image>("Resources/Images/title_background.png", Position(0, 980)));
}

Game::~Game()
{
}

void Game::loadResourcesModels()
{
    /* RESOURCES */
    _resourcesModels.emplace_back("Resources/Food/apple.gltf");
    _resourcesModels.emplace_back("Resources/Gems/blue.gltf");
    _resourcesModels.emplace_back("Resources/Gems/red.gltf");
    _resourcesModels.emplace_back("Resources/Gems/yellow.gltf");
    _resourcesModels.emplace_back("Resources/Gems/cyan.gltf");
    _resourcesModels.emplace_back("Resources/Gems/purple.gltf");
    _resourcesModels.emplace_back("Resources/Gems/green.gltf");
}

void Game::sendMapSize(int width, int height)
{
    _mapWidth = width;
    _mapHeight = height;
}

void Game::getAndSetUpMapTiles()
{
    SetTargetFPS(60);
    std::pair<int, int> mapDimension(0, 0);

    mapDimension = _client->getMapDimension();

    _mapWidth = mapDimension.first;
    _mapHeight = mapDimension.second;

    Vector3 tilePosition = {0, -10, 0};

    for (std::size_t line = 0; line < _mapWidth; line++) {
        for (size_t col = 0; col < _mapHeight; col++) {
            _tiles.emplace_back(std::make_shared<Object::Tile>(_tilesModel, _tilesTexture, _resourcesModels, Position(tilePosition.x, tilePosition.y, tilePosition.z), Object::MAP_OBJECTS::TILES, _camera));
            tilePosition.x += 10.0f;
        }
        tilePosition.z += 10.0f;
        tilePosition.x = 0;
    }
}

void Game::drawTiles()
{
    for (auto &tile : _tiles)
        tile->draw();
}

void Game::drawPlayers()
{
    for (auto &player : _players)
        player->draw();
}

void Game::addPlayerToTeam(std::string const &teamName, int playerId)
{
    _teamsToPlayerId[teamName].push_back(playerId);
}

void Game::addPlayer(int playerId, int x, int y, Object::ORIENTATION orientation, std::string const &teamName)
{
    Position playerPos((float)x, 0, (float)y);

    _players.emplace_back(std::make_shared<Object::Player>(_playersModel, _playersTextures.at(0), _playersAnimation, 1, playerPos * 10, Object::MAP_OBJECTS::PLAYER, playerId, orientation, teamName, _camera, _mapWidth, _mapHeight));
    addPlayerToTeam(teamName, playerId);
    std::cout << "player " << playerId << " was added with position of " << playerPos << " and orientation of " << (int)orientation << " and team name: " << teamName << std::endl;
}

void Game::updatePlayerPosition(int playerId, int x, int y, int orientation)
{
    Position playerPosition(x, 0, y);
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId) {
            player->move(playerPosition * 10);
        }
    }
    std::cout << "player " << playerId << " moved " << x << " " << y << " with orientation: " << orientation << std::endl;
}

void Game::updatePlayerOrientation(int playerId, Object::ORIENTATION orientation)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setOrientation(orientation);
    }
    std::cout << "player " << playerId << " set Orientation to : " << (int)orientation << std::endl;
}

void Game::updatePlayerLevel(int playerId, int level)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setLevel(level);
    }
    std::cout << "player " << playerId << " level is " << level << std::endl;
}

void Game::updatePlayerInventory(int playerId, std::vector<int> const &inventory)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setInventory(inventory);
    }
}

void Game::updateContentMap(response_payload_content_tile_t *content)
{
    std::size_t cpt = 0;
    std::vector<std::pair<Object::PLAYER_RESOURCES, int>> resources;

    std::cout << "updateContentMap" << std::endl;
    for (int index = 0; index < _mapWidth * _mapHeight; index++) {
        resources.emplace_back(Object::PLAYER_RESOURCES::FOOD, content[index].food);
        resources.emplace_back(Object::PLAYER_RESOURCES::LINEMATE, content[index].linemate);
        resources.emplace_back(Object::PLAYER_RESOURCES::DERAUMERE, content[index].deraumere);
        resources.emplace_back(Object::PLAYER_RESOURCES::SIBUR, content[index].sibur);
        resources.emplace_back(Object::PLAYER_RESOURCES::MENDIANE, content[index].mendiane);
        resources.emplace_back(Object::PLAYER_RESOURCES::PHIRAS, content[index].phiras);
        resources.emplace_back(Object::PLAYER_RESOURCES::THYSTAME, content[index].thystame);
        _tiles.at(index)->setResources(resources);
        resources.clear();
    }
}

std::shared_ptr<Object::Tile> Game::getTileByPosition(Position const &position)
{
    for (auto &tile : _tiles) {
        if (tile->getPosition() == position)
            return (tile);
    }
    return nullptr;
}


void Game::updateContentTile(Position const &tilePosition, std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &resources)
{
    getTileByPosition(tilePosition)->setResources(resources);
}

void Game::updatePlayerDead(int playerId)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId) {
            player->die();
            std::cout << "player " << playerId << " died" << std::endl;
        }
    }
}

void Game::updateServerDisconnected()
{
    _isServerConnected = false;
}

void Game::updatePlayerStartIncantation(int playerId)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId) {
            player->startIncantation();
        }
    }
}

void Game::updatePlayerStopIncantation(int playerId, int level)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId) {
            player->stopIncantation(level);
        }
    }
}

void Game::updateInformations(char *data, int type)
{
    std::cout << type << std::endl;
    for (auto &command : _commandsMap)
        if (command.first == type)
            (this->*command.second)(data);
}

void Game::handleAddPlayer(char *data)
{
    response_payload_player_connected_t *addPlayer;

    addPlayer = (response_payload_player_connected_t *)data;
    std::cout << "handleAddPlayer" << std::endl;
    std::cout << addPlayer->team_name << std::endl;


    this->addPlayer(addPlayer->id, addPlayer->position.x, addPlayer->position.y, (Object::ORIENTATION)addPlayer->orientation, std::string(addPlayer->team_name));
}

void Game::handleUpdatePlayerPosition(char *data)
{
    response_payload_player_position_t *playerPos;

    playerPos = (response_payload_player_position_t*)data;
    this->updatePlayerPosition(playerPos->player_id, playerPos->position.x, playerPos->position.y, playerPos->orientation);
}

void Game::handleUpdatePlayerOrientation(char *data)
{
    std::cout << "payer orientation" << std::endl;
    response_payload_player_orientation_t *playerOrientation;

    playerOrientation = (response_payload_player_orientation_t*)data;
    this->updatePlayerOrientation(playerOrientation->player_id, (Object::ORIENTATION)playerOrientation->orientation);
}

void Game::handleUpdatePlayerLevel(char *data)
{
    response_payload_player_level_t *playerLevel;

    playerLevel = (response_payload_player_level_t*)data;
    this->updatePlayerLevel(playerLevel->player_id, playerLevel->level);
}

void Game::handleUpdatePlayerInventory(char *data)
{
    response_payload_player_inventory_t *playerInventory = (response_payload_player_inventory_t*)data;
    std::vector<int> resources;

    resources.emplace_back(playerInventory->food);
    resources.emplace_back(playerInventory->linemate);
    resources.emplace_back(playerInventory->deraumere);
    resources.emplace_back(playerInventory->sibur);
    resources.emplace_back(playerInventory->mendiane);
    resources.emplace_back(playerInventory->phiras);
    resources.emplace_back(playerInventory->thystame);

    this->updatePlayerInventory(playerInventory->player_id, resources);
}

void Game::handleUpdateContentTile(char *data)
{
    response_payload_content_tile_t *contentTile = (response_payload_content_tile_t *)data;
    std::vector<std::pair<Object::PLAYER_RESOURCES, int>> resources;

    resources.emplace_back(Object::PLAYER_RESOURCES::FOOD, contentTile->food);
    resources.emplace_back(Object::PLAYER_RESOURCES::LINEMATE, contentTile->linemate);
    resources.emplace_back(Object::PLAYER_RESOURCES::DERAUMERE, contentTile->deraumere);
    resources.emplace_back(Object::PLAYER_RESOURCES::SIBUR, contentTile->sibur);
    resources.emplace_back(Object::PLAYER_RESOURCES::MENDIANE, contentTile->mendiane);
    resources.emplace_back(Object::PLAYER_RESOURCES::PHIRAS, contentTile->phiras);
    resources.emplace_back(Object::PLAYER_RESOURCES::THYSTAME, contentTile->thystame);

    this->updateContentTile(Position(contentTile->position.x * 10, -10, contentTile->position.y * 10), resources);
}

void Game::handleUpdateContentMap(char *data)
{
    response_payload_content_tile_t *contentMap = (response_payload_content_tile_t *)data;
    this->updateContentMap(contentMap);
}

void Game::handlePlayerDead(char *data)
{
    response_payload_player_dead_t *playerDead = (response_payload_player_dead_t *)data;
    this->updatePlayerDead(playerDead->player_id);
}

void Game::handlePlayerStartIcantation(char *data)
{
    response_payload_player_start_incantation_t *playerIncantation = (response_payload_player_start_incantation_t *)data;
    this->updatePlayerStartIncantation(playerIncantation->player_id);
}

void Game::handlePlayerStopIncantation(char *data)
{
    response_payload_player_end_incantation_t *playerIncantation = (response_payload_player_end_incantation_t *)data;
    this->updatePlayerStopIncantation(playerIncantation->player_id, playerIncantation->player_level);
}



void Game::handleTileClicked()
{
    _shouldPrintTileContent = false;
    bool alreadyClicked = false;
    Position lastTileClicked;

    for (auto &tile : _tiles) {
        if (tile->isClicked()) {
            _shouldPrintTileContent = true;
            _tileResourcesToPrint = tile->getResourcesVector();
            lastTileClicked = tile->getPosition();
        }
    }
    for (auto &tile : _tiles) {
        if (tile->isClicked() && tile->getPosition() != lastTileClicked)
            tile->setIsClicked(false);
    }
}

void Game::handlePlayerClicked()
{
    _shouldPrintPlayerInfos = false;
    for (auto &player : _players) {
        if (player->isClicked()) {
            _playerInfoToPrint = player->getPlayerInfo();
            _shouldPrintPlayerInfos = true;
        }
    }
}

void Game::drawTileResources()
{
    for (int index = 0; index < 13; index = index + 1) {
        _texts.at(index)->draw();
    }
    if (!_isServerConnected)
        _texts.at(14)->draw();
}

void Game::handleTileResources()
{
    for (auto index = 0; index < _tileResourcesToPrint.size(); index = index + 1) {
        std::string tmp = std::to_string(_tileResourcesToPrint.at(index));
        _texts.at(index)->setText(tmp);
    }
}

void Game::drawImages()
{
    for (auto &image : _images)
        image->draw();
}

void Game::drawPlayersInfo()
{
    DrawText(TextFormat("Player Level: %d", _playerInfoToPrint._playerLevel), 20, 50, 20, WHITE);
    DrawText("Player team's name: ", 20, 85, 20, WHITE);
    DrawText(_playerInfoToPrint._teamName.c_str(), 200, 120, 20, WHITE);
    DrawText(TextFormat("Player inventory: \nApple: %d\nLinemate: %d\nDeraumere: %d\nSibur: %d\nMendiane: %d\nPhiras: %d\nThystame: %d", _playerInfoToPrint._inventory.at(0), _playerInfoToPrint._inventory.at(1), _playerInfoToPrint._inventory.at(2), _playerInfoToPrint._inventory.at(3), _playerInfoToPrint._inventory.at(4), _playerInfoToPrint._inventory.at(5), _playerInfoToPrint._inventory.at(6)), 20, 250, 20, WHITE);
}

void Game::draw()
{
    drawImages();
    _camera->startMode3D();
    drawTiles();
    drawPlayers();
    _camera->endMode3D();
    if (_shouldPrintTileContent) drawTileResources();
    if (_shouldPrintPlayerInfos) drawPlayersInfo();
}

Scenes Game::handleEvent()
{
    _nextScene = Scenes::GAME;
    _client->listen();
    for (auto &tile : _tiles)
        tile->handleEvent();
    for (auto &player : _players) {
        player->handleEvent();
        player->animation(player->getCurrentAnimation());
    }
    handleTileClicked();
    handleTileResources();
    handlePlayerClicked();
    return _nextScene;
}
