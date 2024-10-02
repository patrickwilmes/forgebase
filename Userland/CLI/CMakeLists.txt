set(SOURCE
)

add_executable(CLI main.cpp ${SOURCE})
target_link_libraries(CLI PRIVATE Forgebase)