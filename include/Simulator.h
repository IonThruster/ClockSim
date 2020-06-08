#pragma once

#include "Module.h"

enum class SIMULATOR_STATUS
{
    SUCCESS = 0,
    ERROR
};

/// Simulates the whole system
class Simulator
{
    /// Pointer to the top level module
    Module* top_level_;

    /// Maximum simulation time
    size_t max_sim_time_;

    /// Is waveform dumping enabled ?
    /// Note Simulation will be significantly slower in this case.
    bool enable_vcd_;

public:

    /// Ctor.
    ///
    /// @param m Pointer to the top level module
    /// Simulate a maximum of 1000 clocks by default
    Simulator(Module* m)
    : top_level_(m)
    , max_sim_time_(1000)
    , enable_vcd_(false)
    { }

    /// Ctor. with more parameters
    ///
    /// @param m Pointer to the top level module
    /// @param max_time Maximum simulation time allowed
    /// @param enable_vcd Is Waveform Dumping enabled
    Simulator(Module* m, size_t max_time, bool enable_vcd = false)
    : top_level_(m)
    , max_sim_time_(max_time)
    , enable_vcd_(enable_vcd)
    { }

    /// Runs the simulation for max_sim_time clock cycles    
    SIMULATOR_STATUS Run()
    {
        if( enable_vcd_ )
        {
            top_level_->generate_vcd_info();            
        }

        for(size_t clock = 0; clock < max_sim_time_; clock++)
        {
            top_level_->Update(clock);
        }

        if( enable_vcd_ )
        {
            top_level_->dump_vcd();            
        }

        return SIMULATOR_STATUS::SUCCESS;
    }
};