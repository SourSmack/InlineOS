
add_library(inlineos_esp_freertos_deps INTERFACE)


add_library(inlineos_esp_freertos_courier Courier.cpp)
add_library(InlineOS::esp::freertos::Courier ALIAS inlineos_esp_freertos_courier)
target_link_libraries(inlineos_esp_freertos_courier PUBLIC InlineOS::headers PRIVATE inlineos_esp_freertos_deps)

add_library(inlineos_esp_freertos_eventflags EventFlags.cpp)
add_library(InlineOS::esp::freertos::EventFlags ALIAS inlineos_esp_freertos_eventflags)
target_link_libraries(inlineos_esp_freertos_eventflags PUBLIC InlineOS::headers PRIVATE inlineos_esp_freertos_deps)

add_library(inlineos_esp_freertos_eventqueue EventQueue.cpp)
add_library(InlineOS::esp::freertos::EventQueue ALIAS inlineos_esp_freertos_eventqueue)
target_link_libraries(inlineos_esp_freertos_eventqueue PUBLIC InlineOS::headers PRIVATE inlineos_esp_freertos_deps)

#[[add_library(inlineos_esp_freertos_mission Mission.cpp)
add_library(InlineOS::esp::freertos::Mission ALIAS inlineos_esp_freertos_mission)
target_link_libraries(inlineos_esp_freertos_mission PUBLIC InlineOS::headers PRIVATE inlineos_esp_freertos_deps)
#]]
add_library( inlineos_esp_freertos_mission INTERFACE) 
add_library( InlineOS::esp::freertos::Mission ALIAS inlineos_esp_freertos_mission) 
target_include_directories( inlineos_esp_freertos_mission INTERFACE  "${CMAKE_CURRENT_SOURCE_DIR}" )
target_link_libraries( inlineos_esp_freertos_mission INTERFACE inlineos_esp_freertos_deps  InlineOS::Headers) 

add_library(inlineos_esp_freertos INTERFACE)
add_library(InlineOS::esp::freertos ALIAS inlineos_esp_freertos)
target_link_libraries(inlineos_esp_freertos INTERFACE
    InlineOS::esp::freertos::Courier
    InlineOS::esp::freertos::EventFlags
    InlineOS::esp::freertos::EventQueue
    InlineOS::esp::freertos::Mission
)
