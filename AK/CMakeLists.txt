set(SOURCES
        File.cpp
        File.h
        IO.cpp
        IO.h
)

add_library(AK ${SOURCES})
target_include_directories(AK PUBLIC .)