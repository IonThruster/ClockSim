#pragma once

#include "Component.h"
#include <vector>


/// Component which represents a D-Flip Flop.
///
/// Used to model memory element in the simulation
template <typename T>
class Register : public Component
{
    const size_t kLatency_;
    const size_t kCapacity_;
    std::vector<T> values_;
    static size_t id_;

public :

    /// Single Flop
    Register()
    	: Component("Reg", id_), kLatency_(1), kCapacity_(1) {
			id_++;
		}

    /// Flop of certain capacity, and latency
    ///
    /// @param capacity Numebr of elements the flop can hold
    /// @param latency Latency of the flop
    Register(size_t capacity, size_t latency)
    	: Component("Reg", id_), kLatency_(latency), kCapacity_(capacity) {
			id_++;
		}

    /// Setup the connections
    void Setup() 
		{
		}

    /// Initial value for the Flop
    void Init()
		{
		}

    /// What to do at the rising edge of the clock
    void Update()
		{
		}

    /// What to do during Reset
    void Reset()
		{
		}

    /// Push value into a Flop
    void Push()
		{
		}

    /// Pop value from the Flop
    void Pop()
		{
		}

    ~Register()
		{
		}
};


template <typename T>
size_t Register<T>::id_ = 0;
