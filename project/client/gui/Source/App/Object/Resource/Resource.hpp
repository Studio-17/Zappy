/*
** EPITECH PROJECT, 2022
** project
** File description:
** Resources
*/

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

    #include "AThreeDimensionObject.hpp"

namespace Object {
    class Resource : public AThreeDimensionObject {
        public:
            Resource(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources, Position const &position, Object::MAP_OBJECTS type, int quantity);
            Resource(Object::Render::MyModel &pathToModel, Position const &position, Object::MAP_OBJECTS type, int quantity);
            ~Resource();

            void draw() override;

            int getQuantity() const { return _quantity; };
            void setQuantity(int quantity) { _quantity = quantity; };

        protected:
        private:
            int _quantity;
    };
}

#endif /* !RESOURCE_HPP_ */
