add_subdirectory(ipc)
add_subdirectory(drivers)
add_subdirectory(app)
add_subdirectory(input)
# add_subdirectory(ui)

target_sources(app PRIVATE main.c)