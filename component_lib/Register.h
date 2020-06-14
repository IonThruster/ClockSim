#pragma once

#include "Component.h"
#include "Ports.h"

/// Component which represents a D-Flip Flop.
///
/// Used to model memory element in the simulation
/// Inputs are :
///     - in   (input)
///     - rst  (reset)
///     - clk  (clock)
///     - out  (output)
template <typename T, int BIT_WIDTH, int SIZE=1>
class Register : public Component
{
    /// Type of data stored in the Flop
    using FlopDataType = T;

    /// Flop Capacity
    const int kCapacity_ = SIZE;

    /// Value in the flop
    std::array<FlopDataType, SIZE> values_;

    /// Input port
    Port<FlopDataType>* in_;

    /// Output Port
    Port<FlopDataType>* out_;

    /// Reset Port
    Port<bool>* rst_;

    /// Reset Port
    Port<bool>* clk_;

    /// Is flop empty
    bool empty_;

    /// Is full
    bool full_;

    /// Ensures ports have been setup (used for debugging)
    bool config_done_;

    /// Randomize inputs ?
    bool rand_inputs_;

    /// Default Ctor.
    Register() {};

    /// Flip the reset
    bool flip_rst_;

public :

    /// Ctor.
    Register(std::string name, bool random_inputs = false)
        : Component(name)
        , kCapacity_(SIZE)
        , rand_inputs_(random_inputs)
        , flip_rst_(false)
    { 
        srand(0);
    }

    // Default configure is non-sensical TODO : Fix this
    void Configure() { }

    /// Setup the connections
    void Configure(Port<FlopDataType>* in, Port<bool>* rst, Port<FlopDataType>* out,  
                   Port<bool>* clk = nullptr)
    { 
        in_ = in;
        rst_ = rst;

        if(clk) {
            clk_ = clk;
        }

        out_ = out;
        config_done_ = true;
    }

    /// Assign random input value
    void randomize_inputs()
    {
        *in_ = static_cast<FlopDataType>(rand() % 10); 
        *rst_ = static_cast<bool>(rand() % 2);
    }

    /// Reset the entire register(s)
    void reset()
    {
        //#ifdef DEBUG
        //    std::cout << "CALLING RESET\n";
        //#endif

        for(int i = 0; i < kCapacity_; i++)
        {
            values_[i] = static_cast<FlopDataType>(0);
        }
        out_->assign(static_cast<FlopDataType>(0));
        in_->assign(static_cast<FlopDataType>(0));
        
    }

    /// Initial value for the Flop
    void Init()
    {
        reset();
    }

    /// What to do at the rising edge of the clock
    void Update(size_t clock)
	{
        if( clock == 0 ) {
            Init();
        } else if(clock %10 == 0) {
            randomize_inputs();
        }

        // If not reset, move the data
        if( ! rst_->value() ) {
            // Step 1 : Drive output using value
            out_->assign(values_[0]);

            // Step 2 : Move data internally in the flop
            for(int i = 1; i < kCapacity_; i++) {
                values_[i -1] = values_[i];
            }

            // Copy from input
            values_[kCapacity_ - 1] = in_->value();

        // Else reset the whole register(s)
        } else { 
            reset();

            // Reset the reset :)
            if( flip_rst_ ) {
                rst_->assign(0);
                flip_rst_ = false;
            } else {
                flip_rst_ = true;
            }
        }

        //#ifdef DEBUG
        //    std::cout << "Flop Value = " << values_[kCapacity_ - 1] << " Input = " 
        //              << in_->value() << " Output = "  << out_->value() 
        //              << " Reset = " << rst_->value() <<  " Clock = " << clock << std::endl;
        //#endif

	}

    /// What to do during Reset
    void Reset()
	{
        for(int i = 0; i < kCapacity_; i++) {
            values_[i] = T(0);
        } 
	}

    /// VCD Signal declaration info
    void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> > &dumplist) 
    {
        dumplist.push_back({name_ + "_IN", BIT_WIDTH});
        dumplist.push_back({name_ + "_RST", 1});
        dumplist.push_back({name_ + "_OUT", BIT_WIDTH});
    }

    /// VCD Signal Dumping info
    void DumpSignals(std::string module_name) 
    {
        signal_dumper.dump_signal(module_name + "_" + 
                                  name_ + "_IN", convert<FlopDataType, BIT_WIDTH>(in_->value()));
        signal_dumper.dump_signal(module_name + "_" + 
                                  name_ + "_RST", convert<bool, 1>(rst_->value()));
        signal_dumper.dump_signal(module_name + "_" + 
                                  name_ + "_OUT", convert<FlopDataType, BIT_WIDTH>(out_->value()));
    }

    /// Dtor.
    ~Register(){ }
};
