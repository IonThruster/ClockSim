#pragma once

#include "Module.h"

enum class SIMULATOR_STATUS
{
    SUCCESS = 0,
    ERROR
};

/// Simulates the top-level module
class Simulator
{
    Module* top_level_;
    size_t max_sim_time_;
    bool enable_vcd_;
public:

    // Simulate a maximum of 1000 clocks by default
    Simulator(Module* m)
    : top_level_(m)
    , max_sim_time_(1000)
    , enable_vcd_(false)
    { }

    Simulator(Module* m, size_t max_time, bool enable_vcd = false)
    : top_level_(m)
    , max_sim_time_(max_time)
    , enable_vcd_(enable_vcd)
    { }

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