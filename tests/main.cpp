#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <ClockSim.h>

bool Simulate() {
    
    Register<int>("Reg", 10);

    return true;
}
    
// 2 Input 1 Output AND Gate
class AndGate : public Combinatorial<bool, 2, bool, 1>
{

public:
    using Base = Combinatorial<bool, 2, bool, 1>;

    AndGate() : Base("AND_GATE") {}

    AndGate(std::string name) : Base(name) {}

    void Configure(Port<bool>* in_1, Port<bool>* in_2, Port<bool>* out)
    {
        inputs_[0] = in_1;
        inputs_[1] = in_2;

        outputs_[0] = out;
    }

    void logic()
    {
        // Need to dereference properly
        *outputs_[0] = inputs_[0]->value() & inputs_[1]->value();
    }

    void Init()
    {
        // Need to dereference properly
        *inputs_[0] = 0;
        *inputs_[1] = 0;
    }
};


bool Simulate_And()
{

    // 1. Create a top level module
    // 2. Add an And Gate logic
    // 3. Simulate and get result of 2 random inputs.

    Module top ("TOP_LEVEL");

    Port<bool> p1("in1");
    Port<bool> p2("in2");
    Port<bool> p3("out");

    AndGate a("AND_GATE");

    a.Configure(&p1, &p2, &p3);

    top.add(&a);  

   return true;
}



TEST_CASE( "Basic", "[Simulate]" ) {
    REQUIRE( Simulate() == true );
}


TEST_CASE( "And Gate", "[Simulate_And]" ) {
    REQUIRE( Simulate_And() == true );
}

