/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** App
*/

#include "App.hpp"


extern "C" {
    #include "netlib.h"
    #include "protocol/player.h"
    #include "protocol/greeting.h"
    #include "protocol/map.h"
}

static std::vector<std::pair<COMMANDS_GUI, void(App::*)(char *)>> _commandsMap = {
    std::make_pair(PLAYER_CONNECTED, &App::handleAddPlayer),
    std::make_pair(PLAYER_POSITION, &App::handleUpdatePlayerPosition),
    std::make_pair(PLAYER_LEVEL, &App::handleUpdatePlayerLevel),
    std::make_pair(PLAYER_INVENTORY, &App::handleUpdatePlayerInventory),
    std::make_pair(CONTENT_TILE, &App::handleUpdateContentTile),
    std::make_pair(CONTENT_MAP, &App::handleUpdateContentMap)
};

App::App(std::string const &name, int width, int height) : _window(width, height, name), _camera(), _client(), _game()
{
    _camera.setPosition(Position(65, 230, 266));
    _camera.setTarget(Position(65, 0, 65));
    _camera.setFovy(45.0f);
    _camera.setUp(Position(0, 1, 0));
    _camera.setProjection(CAMERA_PERSPECTIVE);
}

App::~App()
{
}

void App::startApp()
{
    try {
        _client.setup();
        _client.connection();
    } catch (ClientErrors const &ClientError) {
        std::cerr << ClientError.what() << std::endl;
    }
    startConnection();
    startMainLoop();
}

void App::startConnection()
{
    std::pair<int, int> mapDimension(0, 0);

    _client._eventsHandler.addNewListener(this);
    mapDimension = _client.getMapDimension();
    _game.sendMapSize(mapDimension.first, mapDimension.second);
    _game.setUpGameMap();
}

void App::startMainLoop()
{
    while (!_window.windowShouldClose()) {
        _client.listen();
        draw();
    }
}

void App::draw()
{
    _window.startDrawing();
    _window.clearBackground(DARKGRAY);
    _camera.startMode3D();
    _game.drawTiles();
    _camera.endMode3D();
    _window.endDrawing();
}

void App::setupOptions(int ac, char **av)
{
    _client.setupOptions(ac, av);
}

void App::handleOptions()
{
    _client.handleOptions();
}

void App::updateInformations(char *data, int type)
{
    for (auto &command : _commandsMap)
        if (command.first == type)
            (this->*command.second)(data);
}

void App::handleAddPlayer(char *data)
{
    response_payload_player_connected_t *addPlayer;

    addPlayer = (response_payload_player_connected_t *)data;

    _game.addPlayer("hello", addPlayer->id, addPlayer->position.x, addPlayer->position.y, (Object::ORIENTATION)addPlayer->orientation);
}

void App::handleUpdatePlayerPosition(char *data)
{
    response_payload_player_position_t *playerPos;

    playerPos = (response_payload_player_position_t*)data;
    _game.updatePlayerPosition(playerPos->player_id, playerPos->position.y, playerPos->position.x);
}

void App::handleUpdatePlayerLevel(char *data)
{
    response_payload_player_level_t *playerLevel;

    playerLevel = (response_payload_player_level_t*)data;
    _game.updatePlayerLevel(playerLevel->player_id, playerLevel->level);
}

void App::handleUpdatePlayerInventory(char *data)
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

    _game.updatePlayerInventory(playerInventory->player_id, resources);
}

void App::handleUpdateContentTile(char *data)
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

    _game.updateContentTile(Position(contentTile->position.x, 0, contentTile->position.y), resources);
}

void App::handleUpdateContentMap(char *data)
{
    response_payload_content_map_t *contentMap = (response_payload_content_map_t *)data;
    _game.updateContentMap(contentMap->content);
}
