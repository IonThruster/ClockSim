add_library(
    clocksim
    Component.h
    Register.h
    Component.cpp
)

set_target_properties(clocksim PROPERTIES 
		LINKER_LANGUAGE CXX
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED YES
)

target_include_directories(clocksim PUBLIC "${CURRENT_CMAKE_SOURCE_DIR}")
