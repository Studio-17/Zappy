/*
** EPITECH PROJECT, 2022
** project
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include "IListener.hpp"

/**
 * @brief A namesapce grouping every scene of the game
 */
    /**
     * @brief An enumeration of every scene of the game
     */
    enum class Scenes {
        MAIN_MENU,
        GAME,
        QUIT
    };

    enum SOUNDS {
        RIGHT_CLICK,
        LEFT_CLICK,
        MOUSE_SCROLL,
        MOUSE_HOVER,
        CLICK_ERROR
    };

    /**
     * @brief An interface of every scene of the game
     */
    class IScene : public IListener {
        public:
            /**
             * @brief Construct a new IScene object
             *
             * @param settings Shared pointer to Settings class
             */
            virtual ~IScene() = default;

            /**
             * @brief To handle every event in the scene
             */
            virtual Scenes handleEvent() = 0;

            /**
             * @brief To draw every object of the Scene
             */
            virtual void draw() = 0;
    };
#endif /* !ISCENE_HPP_ */
