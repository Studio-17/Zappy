/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ressource
*/

#include "Resource.hpp"

Object::Resource::Resource(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Position const &position, Object::MAP_OBJECTS type, int quantity) : AThreeDimensionObject(pathToModel, pathToRessources, position, type), _quantity(quantity)
{
}

Object::Resource::Resource(Object::Render::MyModel &pathToModel, Position const &position, Object::MAP_OBJECTS type, int quantity) : AThreeDimensionObject(pathToModel, position, type), _quantity(quantity)
{

}

Object::Resource::~Resource()
{
}

void Object::Resource::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };
    if (_isEnable)
        DrawModel(_model, modelPosition, _scale, WHITE);
}

