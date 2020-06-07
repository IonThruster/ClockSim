#pragma once

#include "ClockSim.h"


// Module is the basic unit of testing.
// A module in summary is a collection of components and / or modulues according to a specific hierarchy.
// All Simulations models have a TOP_LEVEL module by default.
class Module
{
private :
    std::string name_;
    std::vector<Component*> c_;
public :

    Module(std::string name) : name_(name) {}

    void add(Component* c)
    {
        c_.push_back(c);
    }

};