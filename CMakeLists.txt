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
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -Winline -Wundef -Wcast-qual -Wshadow			\
						 -Wwrite-strings -Wconversion -Wunreachable-code -Wstrict-aliasing=2			\
						 -ffloat-store -fno-common -fstrict-aliasing -Wpointer-arith -Wcast-qual		\
						 -pedantic-errors -Wcast-align -Wchar-subscripts	\
						 -Wcomment -Wconversion -Wdisabled-optimization -Wfloat-equal -Wformat -Wformat=2		\
						 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self		\
						 -Winline -Winvalid-pch -Wunsafe-loop-optimizations  -Wlong-long \
						 -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn	\
						 -Wpacked  -Wparentheses -Wredundant-decls -Wreturn-type -Wsequence-point -Wsign-compare	\
						 -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default			\
						 -Wswitch-enum -Wtrigraphs  -Wuninitialized -Wunknown-pragmas -Wunused -Wunused-function	\
						 -Wunused-label  -Wunused-parameter -Wunused-value -Wunused-variable -Wvariadic-macros		\
						 -Wvolatile-register-var -Wwrite-strings")

# TODO add the following gcc flags -Wpadded -Weffc++ -Waggregate-return -Wmissing-braces

endif()

# Add External Libraries
add_subdirectory(extern)

# ClockSim
add_subdirectory(include)

# Component library built using ClockSim 
include_directories(component_lib)


# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()

# message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
# message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
