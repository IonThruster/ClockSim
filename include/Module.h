#pragma once

#include "ClockSim.h"
#include <vector>


// Module is the basic unit of testing.
// A module in summary is a collection of components and / or modulues according to a specific hierarchy.
// All Simulations models have a TOP_LEVEL module by default.
class Module
{
private :
    std::string name_;
    std::vector<Component*> c_;
    std::vector<Module*> m_;
public :

    Module(std::string name) : name_(name) {}

    void add(Component* c)
    {
        c_.push_back(c);
    }

    void add(Module* m)
    {
        m_.push_back(m);
    }

    void Update(size_t clock)
    {
        // First update all the components inside each module
        for (const auto& component : c_)
        {
            component->Update(clock);
        }

        // Then update all sub-modules
        // Reason is that this produce a nicer looking VCD dump which is easier to debug
        for (const auto& module : m_)
        {
            module->Update(clock);
        }
    }
};