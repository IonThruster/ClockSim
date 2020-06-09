#pragma once

#include "vcdgen.h"
#include <bitset>
#include <string>
#include <list>
#include <tuple>

/// Describes a basic element of simulation.
///
/// Component is the basic element of all simulations and the base class
/// A system consists of Components connected using Nodes.
class Component 
{
    bool construct_done_;
    bool init_done_;

protected :    

    std::string name_;
    
    template<typename T, int width>
    inline std::string convert(T val)
    {
      return std::bitset<width>(val).to_string();
    }

public :    

    /// Object which helps with dumping the VCD
    static VcdGen::VcdGenerator signal_dumper;

    /// constructor with name, id
    /// Default constructor - is disabled
    ///
    /// Gives the instance a name using the parameters passed
    /// @param name Name of the component being instantiated
    Component(std::string name) 
    : name_(name) {}

    /// Sets up the Component
    ///
    /// Sets up all the connections between components.
    /// @attention Should be called only once at the start
    virtual void Configure() = 0;

    /// Updates state info. for the component
    ///
    /// At the rising egde of the clock, the state information of the component needs to be updated.
    /// this method is used to update the state.
    /// @note Should be called every clock - this simulates the pos-edge of clock.
    /// @attention Should be called only after ( Setup() or Reset() )
    /// @see Setup() Reset()
    virtual void Update(size_t clock) = 0;

    /// Asynchronous Reset
    ///
    /// Resets the component back to the initial value, and calls Init()
    /// @note Should be called only if necessary, and after Setup()
    /// @see Setup()
    /// @warning Reset propogation is done automatically, and Reset() will be called on all connected Components.
    virtual void Reset() = 0;

    /// Overload if necessary, for dumping signals
    /// Goal is to generate waveforms using this
    virtual void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> >&) = 0;

    virtual void DumpSignals(std::string) = 0;


    /// Destructor
    virtual ~Component() { };

private:

    /// Initialize vales for the component
    ///
    /// Initial value of the component post Reset()
    /// @attention Should be called only after Setup() or Reset()
    /// @see Setup() Reset()
    virtual void Init() = 0;

};

VcdGen::VcdGenerator Component::signal_dumper{};
