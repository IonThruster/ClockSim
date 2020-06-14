add_library(component_lib INTERFACE)

target_link_libraries(component_lib INTERFACE clocksim)

target_include_directories(component_lib INTERFACE "${CURRENT_CMAKE_SOURCE_DIR}")
