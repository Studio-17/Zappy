/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** App
*/

#include "App.hpp"

App::App(std::string const &name, int width, int height) : _window(width, height, name), _camera()
{
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
}

void App::startMainLoop()
{
    while (!_window.windowShouldClose()) {
        _window.startDrawing();
        _camera.startMode3D();

        _camera.endMode3D();
        _window.endDrawing();
    }
}

void App::setUpOptions(int ac, char **av)
{
    _options.setupOptions(ac, av);
}

void App::handleOptions()
{
    _options.handleOptions();
}
