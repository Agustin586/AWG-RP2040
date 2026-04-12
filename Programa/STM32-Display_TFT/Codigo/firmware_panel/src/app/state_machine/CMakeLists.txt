target_sources(app PRIVATE fsm.c fsm_actions.c signal_actions.c digit.c
                ipc_msg.c)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})