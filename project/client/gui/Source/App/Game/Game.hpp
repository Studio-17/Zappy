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

class Game {
    public:
        Game();
        ~Game();

        void sendMapSize(int width, int height);
        void setUpGameMap();
        void drawTiles();

        void addPlayer(std::string const &team, int playerId, int x, int y);
        void loadRessourcesModels();
        void handlePlayerPosition(int playerId, int x, int y);
        void handlePlayerLevel(int playerId, int level);
        void handlePlayerInventory(int playerId, std::vector<Object::PLAYER_RESSOURCES, int> const &inventory);
        void handleContentMap(std::vector<std::vector<Object::PLAYER_RESSOURCES, int>> const &resources);
        void handleContentTile(Position const &tilePosition, std::vector<Object::PLAYER_RESSOURCES, int> const &resources);

    protected:
    private:
        int _mapWidth;
        int _mapHeight;
        std::vector<std::shared_ptr<Object::Tile>> _tiles;
        // std::vector<std::vector<std::shared_ptr<Object::Tile>>> _tiles2;
        std::vector<std::shared_ptr<Object::Player>> _players;

        Object::Render::MyModel _tilesModel;
        Object::Render::MyModel _playersModel;
        std::vector<Object::Render::MyModel> _resourcesModels;

        Object::Render::MyTexture _tilesTexture;
        std::vector<Object::Render::MyTexture> _playersTextures;

        Object::Render::MyAnimation _playersAnimation;
};

#endif /* !GAME_HPP_ */
