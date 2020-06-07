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
public:

    // Simulate a maximum of 1000 clocks by default
    Simulator(Module* m)
    : top_level_(m)
    , max_sim_time_(1000)
    { }

    Simulator(Module* m, size_t max_time)
    : top_level_(m)
    , max_sim_time_(max_time)
    { }

    SIMULATOR_STATUS Run()
    {
        for(size_t clock = 0; clock < max_sim_time_; clock++)
        {
            top_level_->Update(clock);
        }

        return SIMULATOR_STATUS::SUCCESS;
    }

};