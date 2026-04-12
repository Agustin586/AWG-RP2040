target_sources(app PRIVATE 
    msg_app_to_ipc.c
)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})