set(SOURCE
        FileIndexStore.cpp
        FileIndexStore.h
        SQLiteFileIndexStore.cpp
        SQLiteFileIndexStore.h
        IndexFile.cpp
        IndexFile.h
)

find_package(SQLite3 REQUIRED)

add_library(LibStorage ${SOURCE})
target_link_libraries(LibStorage PRIVATE SQLite::SQLite3 AK)
target_include_directories(LibStorage PUBLIC .)