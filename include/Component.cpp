#include "Component.h"

Component::Component()
{
    name_ = "Component_" + std::to_string(id_);
    id_++;
}

Component::Component(std::string name, size_t id)
{
    name_ = "name" + std::to_string(id);
}

Component::~Component() 
{
    
}

size_t Component::id_ = 0;