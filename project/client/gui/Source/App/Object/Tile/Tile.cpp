/*
** EPITECH PROJECT, 2022
** project
** File description:
** Tile
*/

#include "Tile.hpp"

Object::Tile::Tile(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Position const &position, Object::MAP_OBJECTS type) :
    AThreeDimensionObject(pathToModel, pathToRessources, position, type)
{
    _scale = 0.5f;
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

void Object::Tile::setResources(std::vector<std::shared_ptr<Object::Resource>> const &resources)
{
    _resources = resources;
}
