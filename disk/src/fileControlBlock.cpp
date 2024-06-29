//
// Created by HeChu on 24-6-29.
//

#include <utility>
#include <variant>
#include "Disk/fileInfo.hpp"
#include "Disk/directoryInfo.hpp"

class FileControlBlock {
private:
    std::string name;
    std::variant<FileInfo, DirectoryInfo> info;
public:
    FileControlBlock(std::string name, const FileInfo &info) : name(std::move(name)), info(info) {}

    FileControlBlock(std::string name, const DirectoryInfo &info) : name(std::move(name)), info(info) {}

    explicit FileControlBlock(std::stringstream &data) {
        data >> name;
        int type;
        data >> type;
        if (type == 0) {
            FileInfo fileInfo(data);
            info = fileInfo;
        } else {
            DirectoryInfo directoryInfo;
            info = directoryInfo;
        }
    }

    std::string Name() const {
        return name;
    }

    bool IsDirectory() {
        return std::holds_alternative<DirectoryInfo>(info);
    }
};