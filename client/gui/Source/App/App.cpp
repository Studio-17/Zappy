/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** App
*/

#include "App.hpp"
#include "MainMenu.hpp"

extern "C" {
    #include "netlib.h"
    #include "protocol/player.h"
    #include "protocol/greeting.h"
    #include "protocol/map.h"
}



App::App(std::string const &name, int width, int height) : _window(width, height, name), _client(std::make_shared<Client>())
{
    _camera = std::make_shared<RayLib::CinematicCamera>();
    _camera->setPosition(Position(47, 230, 266));
    _camera->setTarget(Position(37, 0, 55));
    _camera->setFovy(20.0f);
    _camera->setUp(Position(0, 1, 0));
    _camera->setProjection(CAMERA_PERSPECTIVE);
    SetCameraMode(_camera->getCamera(), CAMERA_FREE);
    SetTargetFPS(60);
}

App::~App()
{
}

void App::startApp()
{
    std::shared_ptr<Game> game = std::make_shared<Game>(_client, _camera);
    _menuScenes.emplace(Scenes::GAME, game);
    _menuScenes.emplace(Scenes::MAIN_MENU, std::make_shared<MainMenu>(_client, std::bind(&Game::getAndSetUpMapTiles, game)));
    _activeScene = Scenes::MAIN_MENU;
    _client->_eventsHandler.addNewListener(_menuScenes.at(Scenes::GAME).get());
    startMainLoop();
}

void App::startMainLoop()
{
    while (!_window.windowShouldClose()) {
        _window.startDrawing();
        _window.clearBackground(DARKGRAY);

        _activeScene = _menuScenes.at(_activeScene)->handleEvent();
        if (_activeScene == Scenes::QUIT)
            break;
        _menuScenes.at(_activeScene)->draw();
        _camera->updateCamera();
        _window.endDrawing();
    }
}

void App::setupOptions(int ac, char **av)
{
    _client->setupOptions(ac, av);
}

void App::handleOptions()
{
    _client->handleOptions();
}


