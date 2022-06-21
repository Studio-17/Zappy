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

        void addPlayer(std::string const &team, int playerId, int x, int y);
        void playerPosition(int playerId, int x, int y);
        void playerLevel(int playerId, int level);
        void playerInventory(int playerId, std::vector<std::pair<Object::PLAYER_RESSOURCES, int>> const &inventory);
        void contentTile(Position const &tilePosition, std::vector<std::pair<Object::PLAYER_RESSOURCES, int>> const &resources);
        void contentMap(response_payload_content_tile_t **content);

        std::shared_ptr<Object::Tile> getTileByPosition(Position const &position);

        void loadRessourcesModels();

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
