//
// Created by HeChu on 24-6-30.
//

#include <map>
#include <string>
#include <stdexcept>
#include <charconv>
#include <cstring>
#include "Disk/disk.hpp"

class Dir {
public:
    Dir() = default;

    explicit Dir(const std::string &stream) {
        int offset = 0;
        for (int i = 0; i < maxDirItemNum; i++) {
            std::string name = stream.substr(offset, Disk::MAX_DIR_ITEM_NAME_LENGTH);
            offset += Disk::MAX_DIR_ITEM_NAME_LENGTH;
            auto addressStr = stream.substr(offset, sizeof(int));
            int address;
            std::memcpy(&address, addressStr.data(), sizeof(int));
            offset += sizeof(int);
            if (name.empty() || address == -1) {
                break;
            }
            dirItemMap[name] = address;
        }
    }

    std::string Serialize() {
        std::string stream;
        for (const auto &item: dirItemMap) {
            stream += item.first;
            stream.resize(Disk::MAX_DIR_ITEM_NAME_LENGTH, '\0');
            std::string addressStr(sizeof(int), '\0');
            std::memcpy(addressStr.data(), &item.second, sizeof(int));
            stream += addressStr;
        }
        return stream;
    }

//    const static int dirItemNum = Disk::BLOCK_SIZE / (sizeof(char) * Disk::MAX_DIR_ITEM_NAME_LENGTH + sizeof(int));
    const static int maxDirItemNum = 1024 / (sizeof(char) * 12 + sizeof(int));

    std::map<std::string, int> dirItemMap;

    void AddDirItem(const std::string &name, int address) {
        if(dirItemMap.size() >= maxDirItemNum) throw std::runtime_error("dir item num exceeds limit");
        dirItemMap[name] = address;
    }

private:
};