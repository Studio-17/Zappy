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
}

Game::~Game()
{
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


