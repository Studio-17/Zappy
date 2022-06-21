/*
** EPITECH PROJECT, 2022
** project
** File description:
** Game
*/

#include "Game.hpp"

Game::Game() : _tilesModel("Ressources/Tiles/wall_side.obj"), _playersModel("Ressources/Players/player.iqm"), _tilesTexture("Ressources/Tiles/wall_side.png"), _playersAnimation("Ressources/Players/player.iqm", 1)
{
    _playersTextures.emplace_back("Ressources/Players/cyan.png");
    loadRessourcesModels();
}

Game::~Game()
{
}

void Game::loadRessourcesModels()
{
    /* RESSOURCES */
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

void Game::drawTiles()
{
    for (auto &tile : _tiles)
        tile->draw();
    for (auto &player : _players)
        player->draw();
}

void Game::addPlayer(std::string const &team, int playerId, int x, int y)
{
    Position playerPos((float)x, 0, (float)y);
    (void)team;

    _players.emplace_back(std::make_shared<Object::Player>(_playersModel, _playersTextures.at(0), _playersAnimation, 1, playerPos, Object::MAP_OBJECTS::PLAYER, playerId));
    std::cout << "player " << playerId << " was added" << std::endl;
}

void Game::playerPosition(int playerId, int x, int y)
{
    Position playerPosition(x, 0, y);
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setPosition(playerPosition);
    }
    std::cout << "player " << playerId << " moved " << x << y << std::endl;
}

void Game::playerLevel(int playerId, int level)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setLevel(level);
    }
    std::cout << "player " << playerId << " level is " << level << std::endl;
}

void Game::playerInventory(int playerId, std::vector<std::pair<Object::PLAYER_RESSOURCES, int>> const &inventory)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setInventory(inventory);
    }
}

void Game::contentMap(response_payload_content_tile_t **content)
{
    std::size_t cpt = 0;
    std::vector<std::pair<Object::PLAYER_RESSOURCES, int>> resources;

    for (std::size_t index = 0; index < _mapWidth; index++) {
        for (std::size_t index2 = 0; index2 < _mapHeight; index2++) {
            resources.emplace_back(Object::PLAYER_RESSOURCES::FOOD, content[index][index2].food);
            resources.emplace_back(Object::PLAYER_RESSOURCES::LINEMATE, content[index][index2].linemate);
            resources.emplace_back(Object::PLAYER_RESSOURCES::DERAUMERE, content[index][index2].deraumere);
            resources.emplace_back(Object::PLAYER_RESSOURCES::SIBUR, content[index][index2].sibur);
            resources.emplace_back(Object::PLAYER_RESSOURCES::MENDIANE, content[index][index2].mendiane);
            resources.emplace_back(Object::PLAYER_RESSOURCES::PHIRAS, content[index][index2].phiras);
            resources.emplace_back(Object::PLAYER_RESSOURCES::THYSTAME, content[index][index2].thystame);
            _tiles.at(cpt)->setResources(resources);
            cpt++;
            resources.clear();
        }
    }
}

std::shared_ptr<Object::Tile> Game::getTileByPosition(Position const &position)
{
    for (auto &tile : _tiles)
        if (tile->getPosition() == position)
            return (tile);
    return nullptr;
}


void Game::contentTile(Position const &tilePosition, std::vector<std::pair<Object::PLAYER_RESSOURCES, int>> const &resources)
{
    getTileByPosition(tilePosition)->setResources(resources);
}
