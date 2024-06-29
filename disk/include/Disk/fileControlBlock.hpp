//
// Created by HeChu on 24-6-29.
//

#ifndef FILESYSTEM_FILECONTROLBLOCK_HPP
#define FILESYSTEM_FILECONTROLBLOCK_HPP

#include <variant>
#include "Disk/fileInfo.hpp"
#include "Disk/directoryInfo.hpp"

class FileControlBlock {
private:
    std::string name;
    std::variant<FileInfo, DirectoryInfo> info;
public:
    FileControlBlock(std::string name, const FileInfo& info);

    FileControlBlock(std::string name, const DirectoryInfo& info);

    FileControlBlock(std::stringstream& data);

    std::string Name() const;

    bool IsDirectory();
};
#endif //FILESYSTEM_FILECONTROLBLOCK_HPP
