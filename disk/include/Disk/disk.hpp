//
// Created by HeChu on 24-6-29.
//

#ifndef FILESYSTEM_DISK_HPP
#define FILESYSTEM_DISK_HPP

#include <vector>
#include <memory>
#include <fstream>
#include "Disk/fileControlBlock.hpp"

class Disk {
private:
    int blockNum;
    std::vector<char> bitmap;
    std::fstream file;
    int rootDirAddr;

public:
    explicit Disk(int blockNum, std::fstream &&file);

    explicit Disk(std::fstream &&file);

    ~Disk();

    std::stringstream Serialize();

    static int BlockSizeByByte();

    int BlockNum();

    void WriteBlock(int blockAddr, std::stringstream);

    std::stringstream ReadBlock(int blockAddr);

    std::shared_ptr<FileControlBlock> RootDir();

    static bool IsValidUserName(const std::string &userName);

    static bool IsValidFileOrDirName(const std::string &name);

    static int MaxFileNumberInDir();

    static int MaxFileSizeOf(IndirectFlag indirectFlag);
};

#endif //FILESYSTEM_DISK_HPP
