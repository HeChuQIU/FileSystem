add_library(disk src/disk.cpp
        src/dir.cpp
        include/Disk/dir.hpp
        include/Disk/indexNode.hpp
        src/indexNode'.cpp
)

target_include_directories(disk PRIVATE include)