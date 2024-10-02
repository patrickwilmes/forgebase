set(SOURCE
        FileIndexer.cpp
        FileIndexer.h
)

add_library(LibIndexing ${SOURCE})
target_link_libraries(LibIndexing PRIVATE AK)
target_include_directories(LibIndexing PUBLIC .)