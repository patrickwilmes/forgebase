set(SOURCES
        Forgebase.cpp
        Forgebase.h
        ../Libraries/LibObsidian/Obsidian.cpp
        ../Libraries/LibObsidian/Obsidian.h)
find_package(SQLite3 REQUIRED)

add_library(Forgebase ${SOURCES})

target_link_libraries(Forgebase PRIVATE SQLite::SQLite3 LibObsidian)
target_include_directories(Forgebase PUBLIC .)