/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** App
*/

#include "App.hpp"

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
    startConnection();
    startMainLoop();
}

void App::startConnection()
{
    _game.sendMapSize(12, 12);
    _game.setUpGameMap();
}

void App::startMainLoop()
{
    while (!_window.windowShouldClose()) {
        _window.startDrawing();
        _window.clearBackground(DARKGRAY);
        _camera.startMode3D();

        draw();

        _camera.endMode3D();
        _window.endDrawing();
    }
}

void App::draw()
{
    _game.drawTiles();
}

void App::setUpOptions(int ac, char **av)
{
    _options.setupOptions(ac, av);
}

void App::handleOptions()
{
    _options.handleOptions();
}
