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
    #include <unordered_map>

    #include "Tile.hpp"
    #include "Player.hpp"
    #include "Model.hpp"
    #include "netlib.h"
    #include "protocol/player.h"
    #include "protocol/map.h"
    #include "AScene.hpp"
    #include "Client.hpp"
    #include "IListener.hpp"
    #include "Camera.hpp"
    #include "Text.hpp"
    #include "Resource.hpp"

enum COMMANDS_GUI {
    MAP_SIZE,
    CONTENT_TILE, // STRUCT DONE
    CONTENT_MAP, // STRUCT DONE
    NAME_OF_TEAMS,
    PLAYER_CONNECTED, // STRUCT DONE
    PLAYER_POSITION, // STRUCT DONE
    PLAYER_LEVEL, // STRUCT DONE
    PLAYER_INVENTORY, // STRUCT DONE
    TIME_UNIT,
    TIME_UNIT_MODIFICATION,
    PLAYER_ORIENTATION,
    PLAYER_DEAD,
    SERVER_DISCONNECTED,
    PLAYER_STARTED_INCANTATION,
    PLAYER_ENDED_INCANTATION,
    NB_COMMANDS_GUI,
};

class Game : public AScene {
    public:
        Game(std::shared_ptr<Client> client, std::shared_ptr<RayLib::CinematicCamera> camera);
        ~Game();

        Scenes handleEvent() override;
        void draw() override;

        void sendMapSize(int width, int height);
        void drawTiles();
        void drawPlayers();
        void drawTileResources();
        void drawImages();
        void drawPlayersInfo();

        void addPlayer(int playerId, int x, int y, Object::ORIENTATION orientation, std::string const &teamName);
        void updatePlayerPosition(int playerId, int x, int y, int orientation);
        void updatePlayerOrientation(int playerId, Object::ORIENTATION orientation);
        void updatePlayerLevel(int playerId, int level);
        void updatePlayerInventory(int playerId, std::vector<int> const &inventory);
        void updateContentTile(Position const &tilePosition, std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &resources);
        void updateContentMap(response_payload_content_tile_t *content);

        void handleAddPlayer(char *data);
        void handleUpdatePlayerPosition(char *data);
        void handleUpdatePlayerOrientation(char *data);
        void handleUpdatePlayerLevel(char *data);
        void handleUpdatePlayerInventory(char *data);
        void handleUpdateContentTile(char *data);
        void handleUpdateContentMap(char *data);

        std::shared_ptr<Object::Tile> getTileByPosition(Position const &position);

        void handleTileClicked();
        void handleTileResources();

        void handlePlayerClicked();

        void loadResourcesModels();

        void updateInformations(char *data, int type) override;
        void getAndSetUpMapTiles();

        void addPlayerToTeam(std::string const &teamName, int playerId);
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
        std::shared_ptr<Client> _client;

        std::shared_ptr<RayLib::CinematicCamera> _camera;

        std::unordered_map<std::string, std::vector<int>> _teamsToPlayerId;

        bool _shouldPrintTileContent = false;
        std::vector<int> _tileResourcesToPrint = {0, 0, 0, 0, 0, 0, 0};

        bool _shouldPrintPlayerInfos = false;
        Object::PlayerInfo _playerInfoToPrint;
};

#endif /* !GAME_HPP_ */
