add_executable(sim main.cpp)

target_link_libraries(sim 
                    PRIVATE clocksim
                    PRIVATE catch)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/golden/andsim.vcd   ${CMAKE_CURRENT_BINARY_DIR}/golden/andsim.vcd   COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/golden/circuit.vcd  ${CMAKE_CURRENT_BINARY_DIR}/golden/circuit.vcd  COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/golden/flop.vcd     ${CMAKE_CURRENT_BINARY_DIR}/golden/flop.vcd     COPYONLY)
