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
            _tiles.emplace_back(std::make_shared<Object::Tile>(_tilesModel, _tilesTexture, Position(tilePosition.x, tilePosition.y, tilePosition.z), Object::MAP_OBJECTS::TILES));
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

void Game::handlePlayerPosition(int playerId, int x, int y)
{
    Position playerPosition(x, 0, y);
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setPosition(playerPosition);
    }
    std::cout << "player " << playerId << " moved " << x << y << std::endl;
}

void Game::handlePlayerLevel(int playerId, int level)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setLevel(level);
    }
    std::cout << "player " << playerId << " level is " << level << std::endl;
}

void Game::handlePlayerInventory(int playerId, std::vector<Object::PLAYER_RESSOURCES, int> const &inventory)
{
    for (auto &player : _players) {
        if (player->getPlayerId() == playerId)
            player->setInventory(inventory);
    }
}

void Game::handleContentMap(std::vector<std::vector<Object::PLAYER_RESSOURCES, int>> const &resources)
{
    // for (std::size_t line = 0; line < resources.size(); line++) {
    //     for (size_t col = 0; col < resources.at(line).size(); col++) {
    //         handleContentTile(Position(line, 0, col), resources.at(line));
    //     }
    // }
}

void Game::handleContentTile(Position const &tilePosition, std::vector<Object::PLAYER_RESSOURCES, int> const &resources)
{
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::FOOD)), tilePosition, Object::MAP_OBJECTS::FOOD, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::FOOD))));
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::LINEMATE)), tilePosition, Object::MAP_OBJECTS::LINEMATE, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::LINEMATE))));
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::DERAUMERE)), tilePosition, Object::MAP_OBJECTS::DERAUMERE, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::DERAUMERE))));
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::SIBUR)), tilePosition, Object::MAP_OBJECTS::SIBUR, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::SIBUR))));
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::MENDIANE)), tilePosition, Object::MAP_OBJECTS::MENDIANE, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::MENDIANE))));
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::PHIRAS)), tilePosition, Object::MAP_OBJECTS::PHIRAS, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::PHIRAS))));
    // _tiles.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::THYSTAME)), tilePosition, Object::MAP_OBJECTS::THYSTAME, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::THYSTAME))));


    // TILES2
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::FOOD)), tilePosition, Object::MAP_OBJECTS::FOOD, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::FOOD))));
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::LINEMATE)), tilePosition, Object::MAP_OBJECTS::LINEMATE, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::LINEMATE))));
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::DERAUMERE)), tilePosition, Object::MAP_OBJECTS::DERAUMERE, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::DERAUMERE))));
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::SIBUR)), tilePosition, Object::MAP_OBJECTS::SIBUR, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::SIBUR))));
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::MENDIANE)), tilePosition, Object::MAP_OBJECTS::MENDIANE, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::MENDIANE))));
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::PHIRAS)), tilePosition, Object::MAP_OBJECTS::PHIRAS, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::PHIRAS))));
    // _tiles2.at(tilePosition.getX()).at(tilePosition.getZ())->setResources(std::make_shared<Object::Resource>(_resourcesModels.at(static_cast<int>(Object::PLAYER_RESSOURCES::THYSTAME)), tilePosition, Object::MAP_OBJECTS::THYSTAME, resources.at(static_cast<int>(Object::PLAYER_RESSOURCES::THYSTAME))));
}
