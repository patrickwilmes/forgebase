set(SOURCE
    Obsidian.cpp
    Obsidian.h
)

add_library(LibObsidian ${SOURCE})
target_link_libraries(LibObsidian PRIVATE AK LibIndexing)
target_include_directories(LibObsidian PUBLIC .)