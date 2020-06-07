#pragma once

#include "Component.h"

enum class PortDirection {
    INPUT = 0,
    OUTPUT
};

/// Component which represents a WIRE
template <typename T>
class Port : public Component
{
    T value_;

public :

    /// Single Flop
    Port(std::string name)
    	: Component(name) { }


    /// Where is this connected to
    void Configure()
	{

	}

    /// What to do at the rising edge of the clock
    T value()
	{
        return value_;
	}

    void assign(T val)
    {
        value_ = val;
    }

    void operator=(T val)
    {
        value_ = T(val);
    }

    /// What to do during Reset
    void Reset()
	{

	}

    void Init()
    {

    }

    void Update()
    {

    }

    ~Port(){ }
};