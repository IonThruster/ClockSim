#pragma once

#include "Component.h"
#include "Ports.h"
#include <array>

/// Component which represents a Combo Loigc.
template< typename IN_TYPE, int NUM_IN, typename OUT_TYPE, int NUM_OUT >
class Combinatorial : public Component
{

public :
    std::array<Port<IN_TYPE>*, NUM_IN> inputs_;
    std::array<Port<OUT_TYPE>*, NUM_OUT> outputs_;

    /// Single Flop
    Combinatorial(std::string name)
    	: Component(name) {	}

    /// Initial value for the Flop
    void Configure()
	{
        
	}

    /// What to do at the rising edge of the clock
    ///
    /// WHoever inherits MUST implement this
    void Update(size_t)
    {
        Logic();
    }

    void Logic()
    {

    }

    /// What to do during Reset
    void Reset()
	{

    }

    void Init() = 0;

    ~Combinatorial()
	{
	}
};