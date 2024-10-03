set(SOURCE
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(TUI main.cpp ${SOURCE})
target_link_libraries(TUI PRIVATE Forgebase ${CURSES_LIBRARIES})
