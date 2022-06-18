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

    #include "Tile.hpp"
    #include "Player.hpp"
    #include "Model.hpp"

class Game {
    public:
        Game();
        ~Game();

        void sendMapSize(int width, int height);
        void setUpGameMap();
        void drawTiles();

        void addPlayer(std::string const &team, int playerId, int x, int y);
        void handlePlayerPosition(int playerId, int x, int y);

    protected:
    private:
        int _mapWidth;
        int _mapHeight;
        std::vector<std::shared_ptr<Object::Tile>> _tiles;
        std::vector<std::shared_ptr<Object::Player>> _players;

        Object::Render::MyModel _tilesModel;
        Object::Render::MyModel _playersModel;

        Object::Render::MyTexture _tilesTexture;
        std::vector<Object::Render::MyTexture> _playersTextures;

        Object::Render::MyAnimation _playersAnimation;
};

#endif /* !GAME_HPP_ */
