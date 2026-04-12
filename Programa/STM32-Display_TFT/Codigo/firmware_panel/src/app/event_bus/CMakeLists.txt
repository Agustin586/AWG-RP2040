target_sources(app PRIVATE 
    event_bus.c
)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})