/*
** EPITECH PROJECT, 2022
** project
** File description:
** EventsHandler
*/

#ifndef EVENTSHANDLER_HPP_
#define EVENTSHANDLER_HPP_

    #include <vector>

    #include "IListener.hpp"

class EventsHandler {
    public:
        EventsHandler(){};
        ~EventsHandler(){};

        void addNewListener(IListener *newListener) {
            _listenersVector.push_back(newListener);
        }

        void eventReceive(char *data) {
            for (auto memberToNotify : _listenersVector) {
                memberToNotify->updateInformations(data);
            }
        }

    protected:
    private:
        std::vector<IListener*> _listenersVector;

};

#endif /* !EVENTSHANDLER_HPP_ */
