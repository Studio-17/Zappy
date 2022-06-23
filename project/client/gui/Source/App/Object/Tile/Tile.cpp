/*
** EPITECH PROJECT, 2022
** project
** File description:
** Tile
*/

#include <ctime>
#include "Tile.hpp"

Object::Tile::Tile(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources, std::vector<Object::Render::MyModel> resourcesModels, Position const &position, Object::MAP_OBJECTS type) :
    AThreeDimensionObject(pathToModel, pathToResources, position, type), _resourcesModels(resourcesModels)
{
    _scale = 0.5f;
    _position = position;
    std::srand(std::time(nullptr));

    for (int index = 0; index < static_cast<int>(Object::PLAYER_RESOURCES::NB_RESOURCES); index++) {
        Position newPos = {std::rand() % 10 + position.getX() - 5, position.getY() + 10, std::rand() % 10 + position.getZ() - 5};
        _resources.emplace_back(std::make_shared<Object::Resource>(_resourcesModels.at(index), newPos, static_cast<Object::MAP_OBJECTS>(index + 3), 0));
    }
}

Object::Tile::~Tile()
{
}

void Object::Tile::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };
    if (_isEnable)
        DrawModel(_model, modelPosition, _scale, WHITE);
    for (auto &ressources : _resources)
        ressources->draw();
}

std::vector<std::shared_ptr<Object::Resource>> Object::Tile::getResources() const
{
    return _resources;
}

void Object::Tile::setResources(std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &resources)
{
    for (int index = 0; index < static_cast<int>(Object::PLAYER_RESOURCES::NB_RESOURCES); index++) {
        _resources.at(index)->setQuantity(resources.at(index).second);
    }
}
