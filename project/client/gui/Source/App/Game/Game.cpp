/*
** EPITECH PROJECT, 2022
** project
** File description:
** Game
*/

#include "Game.hpp"

static std::vector<std::pair<COMMANDS_GUI, void(Game::*)(char *)>> _commandsMap = {
    std::make_pair(PLAYER_CONNECTED, &Game::handleAddPlayer),
    std::make_pair(PLAYER_POSITION, &Game::handleUpdatePlayerPosition),
    std::make_pair(PLAYER_LEVEL, &Game::handleUpdatePlayerLevel),
    std::make_pair(PLAYER_INVENTORY, &Game::handleUpdatePlayerInventory),
    std::make_pair(CONTENT_TILE, &Game::handleUpdateContentTile),
    std::make_pair(CONTENT_MAP, &Game::handleUpdateContentMap)
};

Game::Game(std::shared_ptr<Client> client, std::shared_ptr<RayLib::CinematicCamera> camera) : _tilesModel("Resources/Tiles/wall_side.obj"), _playersModel("Resources/Players/player.iqm"), _tilesTexture("Resources/Tiles/wall_side.png"), _playersAnimation("Resources/Players/player.iqm", 1), AScene()
{
    _playersTextures.emplace_back("Resources/Players/cyan.png");
    loadResourcesModels();
    _client = client;
    _camera = camera;
}

Game::Game() : _tilesModel("Resources/Tiles/wall_side.obj"), _playersModel("Resources/Players/player.iqm"), _tilesTexture("Resources/Tiles/wall_side.png"), _playersAnimation("Resources/Players/player.iqm", 1), AScene()
{
    _playersTextures.emplace_back("Resources/Players/cyan.png");
    loadResourcesModels();
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

void Game::setUpGameMap()
{
    Vector3 tilePosition = {0, -10, 0};

    for (std::size_t line = 0; line < _mapWidth; line++) {
        for (size_t col = 0; col < _mapHeight; col++) {
            _tiles.emplace_back(std::make_shared<Object::Tile>(_tilesModel, _tilesTexture, _resourcesModels, Position(tilePosition.x, tilePosition.y, tilePosition.z), Object::MAP_OBJECTS::TILES));
            tilePosition.x += 10.0f;
        }
        tilePosition.z += 10.0f;
        tilePosition.x = 0;
    }
}

void Game::getAndSetUpMapTiles()
{
    std::pair<int, int> mapDimension(0, 0);

    mapDimension = _client->getMapDimension();

    _mapWidth = mapDimension.first;
    _mapHeight = mapDimension.second;

    Vector3 tilePosition = {0, -10, 0};

    for (std::size_t line = 0; line < _mapWidth; line++) {
        for (size_t col = 0; col < _mapHeight; col++) {
            _tiles.emplace_back(std::make_shared<Object::Tile>(_tilesModel, _tilesTexture, _resourcesModels, Position(tilePosition.x, tilePosition.y, tilePosition.z), Object::MAP_OBJECTS::TILES));
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

void Game::addPlayer(std::string const &team, int playerId, int x, int y, Object::ORIENTATION orientation)
{
    Position playerPos((float)x, 0, (float)y);
    (void)team;

    _players.emplace_back(std::make_shared<Object::Player>(_playersModel, _playersTextures.at(0), _playersAnimation, 1, playerPos * 10, Object::MAP_OBJECTS::PLAYER, playerId, orientation));
    std::cout << "player " << playerId << " was added with position of" << playerPos << " and orientation of " << (int)orientation << std::endl;
}

void Game::updatePlayerPosition(int playerId, int x, int y)
{
    Position playerPosition(x, 0, y);
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setPosition(playerPosition * 10);
    }
    std::cout << "player " << playerId << " moved " << x << " " << y << std::endl;
}

void Game::updatePlayerLevel(int playerId, int level)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setLevel(level);
    }
    std::cout << "player " << playerId << " level is " << level << std::endl;
}

void Game::updatePlayerInventory(int playerId, std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &inventory)
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

void Game::updateInformations(char *data, int type)
{
    for (auto &command : _commandsMap)
        if (command.first == type)
            (this->*command.second)(data);
}

void Game::handleAddPlayer(char *data)
{
    response_payload_player_connected_t *addPlayer;

    addPlayer = (response_payload_player_connected_t *)data;

    this->addPlayer("hello", addPlayer->id, addPlayer->position.x, addPlayer->position.y, (Object::ORIENTATION)addPlayer->orientation);
}

void Game::handleUpdatePlayerPosition(char *data)
{
    response_payload_player_position_t *playerPos;

    playerPos = (response_payload_player_position_t*)data;
    printf("%d %d\n", playerPos->position.x, playerPos->position.y);
    this->updatePlayerPosition(playerPos->player_id, playerPos->position.x, playerPos->position.y);
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
    std::vector<std::pair<Object::PLAYER_RESOURCES, int>> resources;

    resources.emplace_back(Object::PLAYER_RESOURCES::FOOD, playerInventory->food);
    resources.emplace_back(Object::PLAYER_RESOURCES::LINEMATE, playerInventory->linemate);
    resources.emplace_back(Object::PLAYER_RESOURCES::DERAUMERE, playerInventory->deraumere);
    resources.emplace_back(Object::PLAYER_RESOURCES::SIBUR, playerInventory->sibur);
    resources.emplace_back(Object::PLAYER_RESOURCES::MENDIANE, playerInventory->mendiane);
    resources.emplace_back(Object::PLAYER_RESOURCES::PHIRAS, playerInventory->phiras);
    resources.emplace_back(Object::PLAYER_RESOURCES::THYSTAME, playerInventory->thystame);

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

void Game::draw()
{
    _camera->startMode3D();
    drawPlayers();
    drawTiles();
    _camera->endMode3D();
}

Scenes Game::handleEvent()
{
    _nextScene = Scenes::GAME;
    _client->listen();
    return _nextScene;
}
