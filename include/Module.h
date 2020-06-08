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

    /// Name of the module
    std::string name_;

    /// Prefix to be added to the module name
    /// Helps identify the full name inclusive of hierarchy
    std::string prefix_;

    /// Components in the module
    std::vector<Component*> c_;

    /// Sub-modules under this module
    std::vector<Module*> m_;

    /// Is it a top level module ?
    bool top_level_;

    /// Is VCD enabled ?
    bool dump_signals_;

public :

    /// Ctor.
    ///
    /// @param name Name of the module
    /// @param top_level Is it a top level module
    /// @warning Only one module should have the top_level flag set
    Module(std::string name, bool top_level = false)
    : name_(name)
    , top_level_(top_level)
    , dump_signals_(false)
    {
        prefix_ = "";
    }

    /// Generates the Signal Declaration Info in the VCD
    ///
    /// Recursivels calls all sub-components and sub-modules
    void generate_vcd_info()
    {
        /// STEP 1 : Call Start Module
        Component::signal_dumper.start_module(name_);

        /// STEP 2 : Add all the signals
        /// First Add all the components inside the current module
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

        /// STEP 3 : End the Module
        Component::signal_dumper.end_module();

        /// End all modules declaration
        if( top_level_ ) {
            dump_signals_ = true;
            Component::signal_dumper.end_all_module_definitions();
        }
    }

    /// Add a component to this module
    ///
    /// @param c Pointer to the Component
    void add(Component* c)
    {
        c_.push_back(c);
    }

    /// Add a Sub-Module to this module
    ///
    /// @param m Pointer to the sub-module
    void add(Module* m)
    {
        m->prefix_ = name_  + m->prefix_;
        m_.push_back(m);
    }

    /// Method that is called every clock
    ///
    /// @param clock Current clock cycle
    /// This method recursively calls Update() for all sub-components and sub-modules
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

    /// Dump the VCD to the console (for now)
    void dump_vcd()
    {
        Component::signal_dumper.dump_vcd();
    }
};