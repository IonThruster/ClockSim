cmake_minimum_required(VERSION 3.10.0)

project(ClockSim VERSION 0.1.0
                 DESCRIPTION "The Cycle-accurate Simulation Framework"
                 LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

endif()

# Add External Libraries
add_subdirectory(extern)

# App built using ClockSim 
#include_directories(clocksim_lib)

# Main ClockSim Lib
add_subdirectory(include)


# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()

# message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
# message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
