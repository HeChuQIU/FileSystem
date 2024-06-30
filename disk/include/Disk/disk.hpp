//
// Created by HeChu on 24-6-29.
//

#ifndef FILESYSTEM_DISK_HPP
#define FILESYSTEM_DISK_HPP

#include <array>
#include <memory>
#include <utility>
#include <fstream>
#include <vector>
#include <vector>
#include "dir.hpp"

class Disk {
public:
    Disk() = default;

    Disk(std::unique_ptr<std::fstream> file);

    const static int BLOCK_SIZE;
    const static int BLOCK_COUNT = 128;
    const static int MAX_DIR_ITEM_NAME_LENGTH;
    const static int MAX_FILE_NAME_LENGTH;
    const static int MAX_USER_NAME_LENGTH;
private:
    std::unique_ptr<std::fstream> file;
    std::array<int, BLOCK_COUNT> fileAllocationTable = {-1};
    std::vector<int> freeBlock;
    Dir rootDir;

    std::string ReadBlock(int blockIndex);

    void WriteBlock(int blockIndex, const std::string &content);

    int SolveDirAddress(const std::string &path);

    Dir GetDirFromAddress(int address);

    std::vector<std::string> Split(const std::string &str, char delimiter);

    std::vector<int> AllocateBlock(int blockNum);

    void FreeBlock(std::vector<int> blockIndexList);

    void MakeDir(const std::string &path);
};

#endif //FILESYSTEM_DISK_HPP
