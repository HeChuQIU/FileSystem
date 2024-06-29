//
// Created by HeChu on 24-6-29.
//

#ifndef FILESYSTEM_FILEINFO_HPP
#define FILESYSTEM_FILEINFO_HPP

#include <sstream>
#include <array>
#include <bitset>
#include "indirectFlag.hpp"

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
    FileInfo();

    FileInfo(int fileSize, std::string owner, std::bitset<6> permission, const int blockAddr[10], int blockAddrIndirect,
             int blockAddrDoubleIndirect,
             int blockAddrTripleIndirect);

    FileInfo(std::stringstream& data);

    std::stringstream Serialize();

    int FileSize() const;

    std::string Owner() const;

    std::bitset<6> Permission() const;

    IndirectFlag IndirectFlag() const;

    std::array<int, 10> BlockAddr() const;

    int BlockAddrIndirect() const;

    int BlockAddrDoubleIndirect() const;

    int BlockAddrTripleIndirect() const;
};

#endif //FILESYSTEM_FILEINFO_HPP
