#pragma once

#include "Component.h"
#include "Ports.h"
#include <array>

/// Component which represents a Combo Loigc.
///
/// @param IN_TYPE Input Data Type
/// @param NUM_IN Number of Inputs to the combo logic
/// @param OUT_TYPE Output Data Type
/// @param NUM_OUT Number of Outputs to the combo logic
template< typename IN_TYPE, int NUM_IN, typename OUT_TYPE, int NUM_OUT >
class Combinatorial : public Component
{
private :
    /// Default Ctor. disabled
    Combinatorial() {}

public :
    /// Input port pointers
    std::array<Port<IN_TYPE>*, NUM_IN> inputs_;

    /// Output port pointers
    std::array<Port<OUT_TYPE>*, NUM_OUT> outputs_;

    /// Ctor.
    ///
    /// @param name Name of the component
    Combinatorial(std::string name)
    : Component(name) {	}

    /// Configure the Combo logic
    virtual void Configure() { };

    /// What to do at the rising edge of the clock
    ///
    /// Whoever inherits MUST implement this
    virtual void Update(size_t)
    {
        Logic();
    }

    /// Logic inside the combinatorial logic
    virtual void Logic() = 0;

    /// What to do during Reset
    virtual void Reset(){ }

    /// Action to perform during Init
    virtual void Init(){ }

    /// VCD signal setup logic
    ///
    /// This helps declare the componponets that will be dumped in the VCD
    virtual void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> >&) = 0;

    /// Dumping Logic
    virtual void DumpSignals(std::string) = 0;

    ~Combinatorial()
	{
	}
};