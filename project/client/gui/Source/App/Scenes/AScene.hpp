/*
** EPITECH PROJECT, 2022
** project
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include <vector>
    #include <memory>

    #include "IScene.hpp"
    #include "Button.hpp"
    #include "Image.hpp"
    #include "Text.hpp"


    /**
     * @brief Abstract class of the scenes of the game
     */
    class AScene : public IScene {
        public:
            /**
             * @brief Construct a new AScene object
             *
             * @param settings Shared pointer to Settings class
             */
            AScene();
            /**
             * @brief Destroy the AScene object
             * 
             */
            virtual ~AScene() = default;

            /**
             * @brief Handle the event of the scene
             * 
             * @return Scenes 
             */
            virtual Scenes handleEvent() = 0;
            /**
             * @brief Draw the scene
             * 
             */
            virtual void draw() = 0;

        protected:
            Scenes _nextScene; ///< Scenes Enum corresponding of the next scene to display / handle

            std::vector<std::unique_ptr<Object::Button>> _buttons; ///< A vector of every Buttons of the scene
            std::vector<std::unique_ptr<Object::Image>> _images; ///< A vector of every Images of the scene
            std::vector<std::unique_ptr<Object::Text>> _texts; ///< A vector of every Texts of the scene
        private:
    };

#endif /* !ASCENE_HPP_ */
