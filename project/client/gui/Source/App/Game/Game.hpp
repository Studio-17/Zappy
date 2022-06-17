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

    protected:
    private:
        int _mapWidth;
        int _mapHeight;
        std::vector<std::shared_ptr<Object::Tile>> _tiles;

        Object::Render::MyModel _tilesModel;
        Object::Render::MyModel _playersModel;

        Object::Render::MyTexture _tilesTexture;
        std::vector<Object::Render::MyTexture> _playersTextures;
};

#endif /* !GAME_HPP_ */
