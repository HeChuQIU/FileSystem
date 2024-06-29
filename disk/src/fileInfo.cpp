//
// Created by HeChu on 24-6-29.
//

#include <sstream>
#include <array>
#include <utility>
#include <bitset>
#include "Disk/indirectFlag.hpp"
#include "Disk/disk.hpp"

class FileInfo {
private:
    int fileSize;
    std::string owner;
    std::bitset<6> permission;
    IndirectFlag indirectFlag;
    std::array<int, 10> blockAddr;
    int blockAddrIndirect;
    int blockAddrDoubleIndirect;
    int blockAddrTripleIndirect;

public:
    FileInfo() = default;

    FileInfo(int fileSize, std::string owner, std::bitset<6> permission, const int blockAddr[10], int blockAddrIndirect,
             int blockAddrDoubleIndirect, int blockAddrTripleIndirect) {
        if (!Disk::IsValidUserName(owner)) {
            throw std::invalid_argument("owner name is invalid");
        }

        this->fileSize = fileSize;
        this->owner = std::move(owner);
        this->permission = permission;
        for (int i = 0; i < 10; i++) {
            this->blockAddr[i] = blockAddr[i];
        }
        this->blockAddrIndirect = blockAddrIndirect;
        this->blockAddrDoubleIndirect = blockAddrDoubleIndirect;
        this->blockAddrTripleIndirect = blockAddrTripleIndirect;
    }

    FileInfo(std::stringstream& data) {
        data.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
        data.read(reinterpret_cast<char *>(&indirectFlag), sizeof(indirectFlag));

        char ownerBuffer[8];
        data.read(ownerBuffer, 8);
        owner = std::string(ownerBuffer);

        data.read(reinterpret_cast<char *>(&permission), sizeof(permission));

        switch (indirectFlag) {
            case DIRECT:
                for (int i = 0; i < 10; i++) {
                    data.read(reinterpret_cast<char *>(&blockAddr[i]), sizeof(blockAddr[i]));
                }
                break;
            case INDIRECT:
                data.read(reinterpret_cast<char *>(&blockAddrIndirect), sizeof(blockAddrIndirect));
                break;
            case DOUBLE_INDIRECT:
                data.read(reinterpret_cast<char *>(&blockAddrDoubleIndirect), sizeof(blockAddrDoubleIndirect));
                break;
            case TRIPLE_INDIRECT:
                data.read(reinterpret_cast<char *>(&blockAddrTripleIndirect), sizeof(blockAddrTripleIndirect));
                break;
        }
    }

    std::stringstream Serialize() {
        std::stringstream data;
        data.write(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));

        auto paddedOwner = owner;
        paddedOwner.resize(8, '\0');
        data.write(paddedOwner.c_str(), 8);

        data.write(reinterpret_cast<char *>(&permission), sizeof(permission));

        data.write(reinterpret_cast<char *>(&indirectFlag), sizeof(indirectFlag));
        switch (indirectFlag) {
            case DIRECT:
                for (int i = 0; i < 10; i++) {
                    data.write(reinterpret_cast<char *>(&blockAddr[i]), sizeof(blockAddr[i]));
                }
                break;
            case INDIRECT:
                data.write(reinterpret_cast<char *>(&blockAddrIndirect), sizeof(blockAddrIndirect));
                break;
            case DOUBLE_INDIRECT:
                data.write(reinterpret_cast<char *>(&blockAddrDoubleIndirect), sizeof(blockAddrDoubleIndirect));
                break;
            case TRIPLE_INDIRECT:
                data.write(reinterpret_cast<char *>(&blockAddrTripleIndirect), sizeof(blockAddrTripleIndirect));
                break;
        }
        return data;
    }

    int FileSize() const {
        return fileSize;
    }

    std::string Owner() const {
        return owner;
    }

    std::bitset<6> Permission() const {
        return permission;
    }

    IndirectFlag IndirectFlag() const {
        return indirectFlag;
    }

    std::array<int, 10> BlockAddr() const {
        return blockAddr;
    }

    int BlockAddrIndirect() const {
        return blockAddrIndirect;
    }

    int BlockAddrDoubleIndirect() const {
        return blockAddrDoubleIndirect;
    }

    int BlockAddrTripleIndirect() const {
        return blockAddrTripleIndirect;
    }
};