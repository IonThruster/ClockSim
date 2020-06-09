add_library(catch INTERFACE)

target_include_directories(catch INTERFACE "${CURRENT_CMAKE_SOURCE_DIR}")

#add_library(
#    catch SHARED
#    catch.hpp
#)
#
#set_target_properties(catch PROPERTIES 
#		LINKER_LANGUAGE CXX
#		CXX_STANDARD 11
#		CXX_STANDARD_REQUIRED YES
#        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/catch/lib
#)
#
#target_include_directories(catch PUBLIC "${CURRENT_CMAKE_SOURCE_DIR}")
