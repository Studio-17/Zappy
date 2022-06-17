/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ressources
*/

#include "Ressources.hpp"

Object::Ressources::Ressources(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Position const &position, Object::MAP_OBJECTS type, int id) :
        AThreeDimensionObject(pathToModel, pathToRessources, position, type)
{
    _id = id;
}

Object::Ressources::~Ressources()
{
}

void Object::Ressources::draw()
{
    Vector3 modelPosition = {
        getPosition().getX(),
        getPosition().getY(),
        getPosition().getZ()
    };
    if (_isEnable)
        DrawModel(_model, modelPosition, _scale, WHITE);
}


