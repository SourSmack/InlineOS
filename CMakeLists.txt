cmake_minimum_required( VERSION 3.16 ) 

project( InlineOS LANGUAGES CXX ) 


add_library( inlineos_headers INTERFACE ) 
add_library( InlineOS::headers ALIAS  inlineos_headers ) 

target_include_directories(inlineos_headers INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory( esp/freertos/ ) 


