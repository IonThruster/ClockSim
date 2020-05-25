#pragma once

#include <string>

/// Describes a basic element of simulation.
///
/// Component is the basic element of all simulations and the base class
/// A system consists of Components connected using Nodes.
class Component 
{
    std::string name_;
    bool construct_done_;
    bool init_done_;

public :

    static size_t id_;

    /// Default constructor
    ///
    /// Gives the instance a automatic name using a ID
    /// @note Try using the constructor with name, id for easier debugging
    Component();

    /// constructor with name, id
    ///
    /// Gives the instance a name using the parameters passed
    /// @param name Name of the component being instantiated
    /// @param id Unique ID of the component
    Component(std::string name, size_t id);

    /// Sets up the Component
    ///
    /// Sets up all the connections between components.
    /// @attention Should be called only once at the start
    virtual void Setup() = 0;

    /// Initialize vales for the component
    ///
    /// Initial value of the component post Reset()
    /// @attention Should be called only after Setup() or Reset()
    /// @see Setup() Reset()
    virtual void Init() = 0;


    /// Updates state info. for the component
    ///
    /// At the rising egde of the clock, the state information of the component needs to be updated.
    /// this method is used to update the state.
    /// @note Should be called every clock - this simulates the pos-edge of clock.
    /// @attention Should be called only after ( Setup() or Reset() ) and Init()
    /// @see Setup() Reset() Init()
    virtual void Update() = 0;


    /// Reset the component
    ///
    /// Resets the component back to the initial value, and calls Init()
    /// @note Should be called only if necessary, and after Setup()
    /// @see Setup()
    /// @warning Reset propogation is done automatically, and Reset() will be called on all connected Components.
    virtual void Reset() = 0;

    /// Overload for printing the Component
    /// 
    /// @param os This is the Ostream object
    /// @param comp Reference to the current Component instance
    /// friend std::ostream& operator<<(std::ostream& os, const Component& comp);

    /// Destructor
    virtual ~Component();
};
