#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Register.h"

bool Simulate() {
    
    Register<int>(10, 10);

    return true;
}

TEST_CASE( "Basic", "[Simulate]" ) {
    REQUIRE( Simulate() == true );
}
