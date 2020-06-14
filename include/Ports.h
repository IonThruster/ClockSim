#pragma once

#include "Component.h"

/// Describes the port direction
enum class PortDirection {
    INPUT = 0,
    OUTPUT
};

/// Component which represents a WIRE
template <typename T>
class Port : public Component
{
    /// Value held by the input port
    /// Technically this is a trasient / temporary
    /// But can be used for simplicity
    T value_;

public :

    /// Ctor.
    Port(std::string name)
    	: Component(name) { }


    /// Where is this connected to
    void Configure(){ }

    /// Returns Temporary value in the "Wire"
    T value()
	{
        return value_;
	}

    /// Assign a value to the "Wire"
    void assign(T val)
    {
        value_ = val;
    }

    /// Operator overloading
    void operator=(T val)
    {
        value_ = T(val);
    }

    /// Nothing to do for Reset for Ports
    void Reset(){ }

    /// Nothing to do for Init for Ports
    void Init(){ }

    /// Nothing to do for Update for Ports
    void Update(size_t){ }

    /// Nothing to do for VCD genration for Ports
    virtual void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> >&) { };

    /// Nothing to do for VCD Generation for Ports
    virtual void DumpSignals(std::string) { };

    /// Dtor.
    ~Port(){ }
};
