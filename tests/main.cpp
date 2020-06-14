#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <ClockSim.h>
#include <logic_gates.h>

#include <iostream>
#include <stdlib.h>
#include <list>
#include <tuple>

/// Basic test - tests compilation
bool Simulate() {
    
    Register<int>("Reg", 10);

    return true;
}

/// Simulates a 2 Input 1 output AND gate
bool Simulate_And()
{

    // 1. Create a top level module
    // 2. Add the And Gate logic to the module
    // 3. Add the top level module to the simulator
    // 4. Run Simulation

    Module top ("TOP_LEVEL", true);

    Port<bool> p1("in1");
    Port<bool> p2("in2");
    Port<bool> p3("out");

    AndGate a("AND_GATE", true);
    a.Configure(&p1, &p2, &p3);

    top.add(&a);

    Simulator And_Sim(&top, 100, true, "andsim.vcd");

    if( And_Sim.Run() == SIMULATOR_STATUS::SUCCESS ) {
        return true;    
    } else {
        return false;
    }
}

/// Simulates the following circuit
///   ---> AND
///            ---> AND --->
///   ---> OR
bool Simulate_Circuit()
{
    // 1. Create a top level module
    // 2. Add the And Gate logic to the module
    // 3. Add the top level module to the simulator
    // 4. Run Simulation
    
    Module top ("TOP_LEVEL", true);
    
    // First AND Gate
    Port<bool> p1("and1_in1");
    Port<bool> p2("and1_in2");
    Port<bool> p3("and1_out");

    AndGate a1("AND1_GATE", true);
    a1.Configure(&p1, &p2, &p3);
    top.add(&a1);

    // Or Gate
    Port<bool> p4("or1_in1");
    Port<bool> p5("or1_in2");
    Port<bool> p6("or1_out");

    OrGate o1("OR_GATE", true);
    o1.Configure(&p4, &p5, &p6);
    top.add(&o1);

    // Final output and gate
    Port<bool> p7("and2_out");

    AndGate a2("AND2_GATE");
    a2.Configure(&p3, &p6, &p7);
    top.add(&a2);

    Simulator Circuit_Sim(&top, 100, true, "circuit.vcd");

    if( Circuit_Sim.Run() == SIMULATOR_STATUS::SUCCESS ) {
        return true;    
    } else {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///
///   Catch-2 test cases
///
///////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Basic", "[Simulate]" ) {
    REQUIRE( Simulate() == true );
}


TEST_CASE( "And Gate", "[Simulate_And]" ) {
    REQUIRE( Simulate_And() == true );
}


TEST_CASE( "Circuit", "[Simulate_Circuit]" ) {
    REQUIRE( Simulate_Circuit() == true );
}
