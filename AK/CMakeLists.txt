set(SOURCES
        File.cpp
        File.h
        IO.cpp
        IO.h
        UserSpace.cpp
        UserSpace.h
)

add_library(AK ${SOURCES})
target_include_directories(AK PUBLIC .)