#pragma once

#include "ClockSim.h"
#include <vector>

// Debug
#include <iostream>


// Module is the basic unit of testing.
// A module in summary is a collection of components and / or modulues according to a specific hierarchy.
// All Simulations models have a TOP_LEVEL module by default.
class Module
{
private :
    std::string name_;

    // Indicates the full name inclusive of hierarchy
    std::string prefix_;

    std::vector<Component*> c_;
    std::vector<Module*> m_;
    bool top_level_;
    bool dump_signals_;
public :

    Module(std::string name, bool top_level = false)
    : name_(name)
    , top_level_(top_level)
    , dump_signals_(false)
     {
        prefix_ = "";
     }

    void generate_vcd_info()
    {              
        Component::signal_dumper.start_module(name_);

        // First Add all the components inside the current module
        for (const auto& component : c_)
        {

            std::list< std::tuple<std::string, uint16_t> > dumplist;
            component->generate_vcd_info(dumplist);
            for(const auto &d : dumplist) {                
                Component::signal_dumper.add_signal(std::get<0>(d), std::get<1>(d));
            }
        }                    

        // Then update all sub-modules
        // Reason is that this produce a nicer looking VCD dump which is easier to debug
        for (const auto& module : m_)
        {
            module->generate_vcd_info();
        }

        Component::signal_dumper.end_module();

        if( top_level_ ) {
            dump_signals_ = true;
            Component::signal_dumper.end_all_module_definitions();
        }
    }

    void add(Component* c)
    {
        c_.push_back(c);
    }

    void add(Module* m)
    {
        m->prefix_ = name_  + m->prefix_;
        m_.push_back(m);
    }

    void Update(size_t clock)
    {
        // First update all the components inside each module
        for (const auto& component : c_)
        {
            if( dump_signals_ )
            {
                if( top_level_ )
                {
                    Component::signal_dumper.dump_time(clock);
                }                
                component->DumpSignals(prefix_ + name_);
            }
            component->Update(clock);
        }

        // Then update all sub-modules
        // Reason is that this produce a nicer looking VCD dump which is easier to debug
        for (const auto& module : m_)
        {
            module->Update(clock);
        }
    }

    void dump_vcd()
    {
        Component::signal_dumper.dump_vcd();
    }
};