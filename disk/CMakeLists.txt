add_library(disk src/disk.cpp
        src/fileControlBlock.cpp
        src/fileInfo.cpp
        src/directoryInfo.cpp
        include/Disk/fileInfo.hpp
        include/Disk/directoryInfo.hpp
        include/Disk/fileControlBlock.hpp
)

target_include_directories(disk PRIVATE include)