set(SOURCES
        File.cpp
        File.h
        IO.cpp
        IO.h
        UserSpace.cpp
        UserSpace.h
        Ini.cpp
        Ini.h
        Strings.cpp
        Strings.h
        Logging.cpp
        Logging.h
        Terminal.cpp
        Terminal.h
)
message(STATUS "AK Include directories: ${CMAKE_CURRENT_SOURCE_DIR}")
add_library(AK ${SOURCES})
target_include_directories(AK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
