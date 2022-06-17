/*
** EPITECH PROJECT, 2022
** project
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_

    #include "AThreeDimensionObject.hpp"
    #include "Ressources.hpp"

namespace Object {
    class Tile : public AThreeDimensionObject {
        public:
            Tile(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Position const &position, Object::MAP_OBJECTS type);
            ~Tile();

            void draw() override;

        protected:
        private:
            std::vector<std::shared_ptr<Ressources>> _ressources;
    };
}

#endif /* !TILE_HPP_ */
