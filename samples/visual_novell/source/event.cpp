#include "event.hpp"

Event::Event(const std::string &name, const std::string &message, const std::string &sceneName) : 
    _name(name),
    _message(message),
    _sceneName(sceneName)
{
}

std::string Event::GetName() const
{
    return _name;
}

std::string Event::GetMessage() const
{
    return _message;
}

std::string Event::GetSceneName() const
{
    return _sceneName;
}

std::string Event::ToJSON() const
{
    return std::string("{\"name\":\"") + this->GetName() + 
        std::string("\",\"message\":\"") + this->GetMessage() +
        std::string("\",\"sceneName\":\"") + this->GetSceneName() +
        std::string("\"}");
}

bool operator==(const Event& left, const Event& right){
    return left.GetName() == right.GetName();
}