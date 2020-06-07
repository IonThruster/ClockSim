#pragma once

#include "Component.h"
#include "Ports.h"

/// Component which represents a D-Flip Flop.
///
/// Used to model memory element in the simulation
template <typename T>
class Register : public Component
{
    const size_t kCapacity_;
    std::vector<T> values_;
    Port<T>* in_;
    Port<T>* out_;

public :

    /// Single Flop
    Register(std::string name)
    	: Register(name, 1, 1) {
		}

    /// Flop of certain capacity, Flop can contain arbitrary datatypes
    ///
    /// @param capacity Numebr of elements the flop can hold
    Register(std::string name, size_t capacity)
    	: Component(name), kCapacity_(capacity) {
		}

    /// Setup the connections
    void Configure() 
		{
		}

    /// Initial value for the Flop
    void Init()
		{
      for(size_t i = 0; i < kCapacity_; i++)
      {
        values_.push_back(T(0));
      }
		}

    /// What to do at the rising edge of the clock
    void Update(size_t)
		{
      out_->assign(values_[kCapacity_-1]);

      for(size_t i = 1; i < kCapacity_; i++) {
        values_[i] = values_[i-1];
      }

      values_[0] = in_->value();
		}

    /// What to do during Reset
    void Reset()
		{
      for(size_t i = 0; i < kCapacity_; i++) {
        values_[i] = T(0);
      } 
		}

    virtual void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> > &) { };

    virtual void DumpSignals(std::string) { };

    ~Register()
		{
		}
};