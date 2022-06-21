/*
** EPITECH PROJECT, 2022
** project
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

    #include <memory>
    #include <vector>
    #include <map>

    #include "Tile.hpp"
    #include "Player.hpp"
    #include "Model.hpp"
    #include "netlib.h"
    #include "protocol/player.h"
    #include "protocol/map.h"

class Game {
    public:
        Game();
        ~Game();

        void sendMapSize(int width, int height);
        void setUpGameMap();
        void drawTiles();

        void addPlayer(std::string const &team, int playerId, int x, int y, Object::ORIENTATION orientation);
        void updatePlayerPosition(int playerId, int x, int y);
        void updatePlayerLevel(int playerId, int level);
        void updatePlayerInventory(int playerId, std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &inventory);
        void updateContentTile(Position const &tilePosition, std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &resources);
        void updateContentMap(response_payload_content_tile_t **content);

        std::shared_ptr<Object::Tile> getTileByPosition(Position const &position);

        void loadResourcesModels();

    protected:
    private:
        int _mapWidth;
        int _mapHeight;

        std::vector<std::shared_ptr<Object::Tile>> _tiles;
        std::vector<std::shared_ptr<Object::Player>> _players;

        Object::Render::MyModel _tilesModel;
        Object::Render::MyModel _playersModel;
        std::vector<Object::Render::MyModel> _resourcesModels;

        Object::Render::MyTexture _tilesTexture;
        std::vector<Object::Render::MyTexture> _playersTextures;

        Object::Render::MyAnimation _playersAnimation;
};

#endif /* !GAME_HPP_ */
