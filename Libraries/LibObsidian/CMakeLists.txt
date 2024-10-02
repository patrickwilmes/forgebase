set(SOURCE
    Obsidian.cpp
    Obsidian.h
)

add_library(LibObsidian ${SOURCE})
target_include_directories(LibObsidian PUBLIC .)