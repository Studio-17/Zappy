/*
** EPITECH PROJECT, 2022
** project
** File description:
** Tile
*/

#include "Tile.hpp"

Object::Tile::Tile(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, std::vector<Object::Render::MyModel> resourcesModels, Position const &position, Object::MAP_OBJECTS type) :
    AThreeDimensionObject(pathToModel, pathToRessources, position, type), _resourcesModels(resourcesModels)
{
    _scale = 0.5f;

    setPosition(position);
    for (int index = 0; index < static_cast<int>(Object::PLAYER_RESSOURCES::THYSTAME); index++) {
        _resources.emplace_back(std::make_shared<Object::Resource>(_resourcesModels.at(index), position, static_cast<Object::MAP_OBJECTS>(index + 3), 0));
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
}

std::vector<std::shared_ptr<Object::Resource>> Object::Tile::getResources() const
{
    return _resources;
}

void Object::Tile::setResources(std::vector<std::pair<Object::PLAYER_RESSOURCES, int>> const &resources)
{
    for (int index = 0; index < static_cast<int>(Object::PLAYER_RESSOURCES::THYSTAME); index++) {
        _resources.at(index)->setQuantity(resources.at(index).second);
    }
}
