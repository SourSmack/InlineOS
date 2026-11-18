cmake_minimum_required( VERSION 3.16 ) 

project( InlineOS LANGUAGES CXX ) 


# sharing headers for TU files 
add_library( inlineos_headers INTERFACE ) 
add_library( InlineOS::headers ALIAS  inlineos_headers ) 
target_include_directories(inlineos_headers INTERFACE
    # either from source or .obj
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

#registering target 
add_subdirectory( esp/freertos/ ) 


