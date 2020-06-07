add_library(
    clocksim
    ClockSim.h
    Component.h
    Register.h
    Ports.h
    Combo.h
    Module.h
)

set_target_properties(clocksim PROPERTIES 
		LINKER_LANGUAGE CXX
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED YES
)

target_include_directories(clocksim PUBLIC "${CURRENT_CMAKE_SOURCE_DIR}")
