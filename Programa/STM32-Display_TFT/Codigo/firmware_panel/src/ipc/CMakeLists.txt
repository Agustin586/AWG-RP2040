target_sources(app PRIVATE
  ipc_thread.c
  ipc_master.c
  ipc_parser.c
)

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})