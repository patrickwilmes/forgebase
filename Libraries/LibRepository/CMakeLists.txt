set(SOURCE
        CodeRepository.cpp
        CodeRepository.h
)

add_library(LibRepository ${SOURCE})
target_link_libraries(LibRepository PRIVATE AK LibIndexing)
target_include_directories(LibRepository PUBLIC .)