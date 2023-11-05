#include "scene.hpp"

#include <algorithm>

Scene::Scene(const Scene &other) : _name(other.GetName()), _events(other._events), _messages(other._messages)
{
}

Scene Scene::Load(const std::string &json)
{
    return Scene();
}

Event Scene::GetEvent(const std::string &eventName) const
{
    struct IsValidEvent
    {
        std::string _eventName;
        IsValidEvent(const std::string &eventName) : _eventName(eventName) {}
        bool operator()(const Event &e) const
        {
            return _eventName == e.GetName();
        }
    };
    auto it = std::find(_events.begin(), _events.end(), IsValidEvent(eventName));
}

std::string Scene::GetName() const
{
    return _name;
}

bool operator==(const Scene& left, const Scene& right){
    return left.GetName() == right.GetName();
}

bool operator!=(const Scene& left, const Scene& right){
    return !(left == right);
}

void Scene::Draw(const Painter& painter) {
    // TODO
    for(auto& message: _messages){
        painter.PrintMessage(message);
    }
}