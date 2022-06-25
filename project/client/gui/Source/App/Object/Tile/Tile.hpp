/*
** EPITECH PROJECT, 2022
** project
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_

    #include "AThreeDimensionObject.hpp"
    #include "Resource.hpp"
    #include "Camera.hpp"

namespace Object {
    class Tile : public AThreeDimensionObject {
        public:
            Tile(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources,  std::vector<Object::Render::MyModel> resourcesModels, Position const &position, Object::MAP_OBJECTS type, std::shared_ptr<RayLib::CinematicCamera> camera);
            ~Tile();

            void draw() override;
            void handleEvent();

            std::vector<std::shared_ptr<Object::Resource>> getResources() const;
            void setResources(std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &resources);
            std::vector<int> getResourcesVector() const;

            Position getPosition() const { return _position; }
            void setPosition(Position const &position) { _position = position; }

            void drawTileBounds();

            bool isClicked() const { return _isClicked; };
            void setIsClicked(bool isClicked) {
                _tilesCollision.hit = isClicked;
                _isClicked = isClicked;
            };

            bool isIncanted() const { return _isIncanted; };
            void incanteTile() {
                std::cout << "tile incanted !" << std::endl;
                _isIncanted = true;
            };

        protected:
        private:
            std::vector<std::shared_ptr<Object::Resource>> _resources;
            std::vector<Object::Render::MyModel> _resourcesModels;

            std::shared_ptr<RayLib::CinematicCamera> _camera;

            Position _position;
            Ray _mouseRay = { 0 };
            RayCollision _tilesCollision = { 0 };
            BoundingBox _boundingBox;
            bool _isIncanted = false;

            bool _isClicked = false;
    };
}

#endif /* !TILE_HPP_ */
