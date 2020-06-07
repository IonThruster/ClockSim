#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include <ClockSim.h>
#include <stdlib.h>
#include <list>
#include <tuple>

bool Simulate() {
    
    Register<int>("Reg", 10);

    return true;
}
    
// 2 Input 1 Output AND Gate
class AndGate : public Combinatorial<bool, 2, bool, 1>
{
    bool config_done_;

public:
    using Base = Combinatorial<bool, 2, bool, 1>;

    AndGate(std::string name) 
    : Base(name)
    , config_done_(false) {

        srand (0);
    }

    void Configure(Port<bool>* in_1, Port<bool>* in_2, Port<bool>* out)
    {
        inputs_[0] = in_1;
        inputs_[1] = in_2;

        outputs_[0] = out;
        config_done_ = true;
    }

    void Logic()
    {
        assert(config_done_);

        // Need to dereference properly
        *outputs_[0] = inputs_[0]->value() & inputs_[1]->value();
    }

    void randomize_inputs()
    {
        *inputs_[0] = static_cast<bool>(rand() % 2); 
        *inputs_[1] = static_cast<bool>(rand() % 2);
    }

    void Update(size_t clock)
    {
        if(clock % 10 == 0)
        {
            randomize_inputs();
        }

        Logic();
    }

    void Init()
    {
        // Need to dereference properly
        *inputs_[0] = 0;
        *inputs_[1] = 0;
    }

    void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> > &dumplist)
    {
        dumplist.push_back({"IN_1", 1});
        dumplist.push_back({"IN_2", 1});
        dumplist.push_back({"OUT", 1});
    }

    void DumpSignals(std::string module_name)
    {
        signal_dumper.dump_signal(module_name + "_IN_1", convert<bool, 1>(inputs_[0]->value()));
        signal_dumper.dump_signal(module_name + "_IN_2", convert<bool, 1>(inputs_[1]->value()));
        signal_dumper.dump_signal(module_name + "_OUT", convert<bool, 1>(outputs_[0]->value()));
    }
};

bool Simulate_And()
{

    // 1. Create a top level module
    // 2. Add an And Gate logic
    // 3. Simulate and get result of 2 random inputs.

    Module top ("TOP_LEVEL", true);

    Port<bool> p1("in1");
    Port<bool> p2("in2");
    Port<bool> p3("out");

    AndGate a("AND_GATE");
    a.Configure(&p1, &p2, &p3);

    top.add(&a);

    Simulator And_Sim(&top, 100, true);

    if( And_Sim.Run() == SIMULATOR_STATUS::SUCCESS )
    {
        std::cout << "SUCCESSFUL RUN\n";
    }

    return true;
}



TEST_CASE( "Basic", "[Simulate]" ) {
    REQUIRE( Simulate() == true );
}


TEST_CASE( "And Gate", "[Simulate_And]" ) {
    REQUIRE( Simulate_And() == true );
}

