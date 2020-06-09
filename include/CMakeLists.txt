add_library(clocksim INTERFACE)

target_link_libraries(clocksim INTERFACE vcdgen)

target_include_directories(clocksim INTERFACE "${CURRENT_CMAKE_SOURCE_DIR}")

#add_library(
#    clocksim SHARED
#    ClockSim.h
#    Component.h
#    Register.h
#    Ports.h
#    Combo.h
#    Module.h
#    Simulator.h
#)
#
#target_link_libraries(clocksim vcdgen)
#
#set_target_properties(clocksim PROPERTIES 
#		LINKER_LANGUAGE CXX
#		CXX_STANDARD 11
#		CXX_STANDARD_REQUIRED YES
#        	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/clocksim/lib
#)
#
#target_include_directories(clocksim PUBLIC "${CURRENT_CMAKE_SOURCE_DIR}")
#
#message("PROJECT_BINARY_DIR is ${PROJECT_BINARY_DIR}")
