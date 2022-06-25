/*
** EPITECH PROJECT, 2022
** project
** File description:
** Tile
*/

#include "Tile.hpp"

Object::Tile::Tile(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources, std::vector<Object::Render::MyModel> resourcesModels, Position const &position, Object::MAP_OBJECTS type, std::shared_ptr<RayLib::CinematicCamera> camera) :
    AThreeDimensionObject(pathToModel, pathToResources, position, type), _resourcesModels(resourcesModels)
{
    _scale = 0.5f;
    _position = position;
    _camera = camera;
    _boundingBox = {(BoundingBox){(Vector3){ getPosition().getX() - 5, getPosition().getY() + (float)9.99, getPosition().getZ() - 5 },
                                  (Vector3){ getPosition().getX() + 5, getPosition().getY() + 10, getPosition().getZ() + 5 }}};

    for (int index = 0; index < static_cast<int>(Object::PLAYER_RESOURCES::NB_RESOURCES); index++) {
        Position newPos = {std::rand() % 9 + position.getX() - 5, position.getY() + 10, std::rand() % 9 + position.getZ() - 5};
        _resources.emplace_back(std::make_shared<Object::Resource>(_resourcesModels.at(index), newPos, static_cast<Object::MAP_OBJECTS>(index + 3), 0));
    }
}

Object::Tile::~Tile()
{
}

void Object::Tile::handleEvent()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!_tilesCollision.hit) {
            _mouseRay = GetMouseRay(GetMousePosition(), _camera->getCamera());
            _tilesCollision = GetRayCollisionBox(_mouseRay,
            (BoundingBox){(Vector3){ getPosition().getX() - 5, getPosition().getY(), getPosition().getZ() - 5 },
                                              (Vector3){ getPosition().getX() + 10, getPosition().getY() + 5, getPosition().getZ() + 5 }});
        }
        else
            _tilesCollision.hit = false;
    }
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

    if (_tilesCollision.hit) {
        DrawBoundingBox(_boundingBox, RED);
        _isClicked = true;
    } else {
        DrawBoundingBox(_boundingBox, ORANGE);
        _isClicked = false;
    }
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

std::vector<int> Object::Tile::getResourcesVector() const
{
    std::vector<int> tmp;

    for (auto &resource : _resources) {
        tmp.push_back(resource->getQuantity());
    }
    return tmp;
}