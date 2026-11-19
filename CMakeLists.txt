cmake_minimum_required( VERSION 3.16 ) 

project( InlineOS LANGUAGES CXX ) 

include(FetchContent)
FetchContent_Declare(
    etl 
    GIT_REPOSITORY https://github.com/ETLCPP/etl.git
    GIT_TAG        20.38.14  # lub wybrany stabilny tag
    GIT_SHALLOW TRUE 
    SOURCE_SUBDIR  skip_cmake
)
add_library( etl_lib INTERFACE ) 
target_link_libraries( etl_lib INTERFACE "${etl_SOURCE_DIR}/include" )

# sharing headers for TU files 
add_library( inlineos_headers INTERFACE ) 
add_library( InlineOS::headers ALIAS  inlineos_headers ) 
target_include_directories(inlineos_headers INTERFACE
    # either from source or .obj
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>

    etl_lib
)

#registering target 
add_subdirectory( esp/freertos/ ) 


