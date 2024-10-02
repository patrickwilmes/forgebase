set(SOURCES
        Forgebase.cpp
        Forgebase.h
)
find_package(SQLite3 REQUIRED)

add_library(Forgebase ${SOURCES})

target_link_libraries(Forgebase PRIVATE SQLite::SQLite3 LibObsidian AK LibIndexing LibStorage LibRepository)
target_include_directories(Forgebase PUBLIC .)