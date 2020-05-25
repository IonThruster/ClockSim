add_library(
    catch SHARED
    catch.hpp
)

set_target_properties(catch PROPERTIES 
		LINKER_LANGUAGE CXX
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED YES
)

target_include_directories(catch PUBLIC "${CURRENT_CMAKE_SOURCE_DIR}")
