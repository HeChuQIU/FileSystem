//
// Created by HeChu on 24-6-28.
//

#include <array>
#include <fstream>
#include <memory>
#include <map>
#include <vector>
#include <sstream>
#include "Disk/dir.hpp"


class Disk {
public:
    Disk() = default;

    Disk(std::unique_ptr<std::fstream> file) : file(std::move(file)) {}

    const static int BLOCK_SIZE = 1024;
    const static int BLOCK_COUNT = 128;
    const static int MAX_DIR_ITEM_NAME_LENGTH = 12;
    const static int MAX_FILE_NAME_LENGTH = 16;
    const static int MAX_USER_NAME_LENGTH = 16;
private:
    std::unique_ptr<std::fstream> file;
    std::array<int, BLOCK_COUNT> fileAllocationTable = {-1};
    std::vector<int> freeBlock;
    Dir rootDir;

    std::string ReadBlock(int blockIndex) {
        file->seekg(blockIndex * BLOCK_SIZE);
        char buffer[BLOCK_SIZE];
        file->read(buffer, BLOCK_SIZE);
        return buffer;
    }

    void WriteBlock(int blockIndex, const std::string &content) {
        if (content.size() > BLOCK_SIZE) throw std::runtime_error("content size exceeds block size");
        file->seekp(blockIndex * BLOCK_SIZE);
        file->write(content.c_str(), BLOCK_SIZE);
    }

    int SolveDirAddress(const std::string &path) {
        std::vector<std::string> pathList = Split(path, '/');
        Dir currentDir = rootDir;
        for (const auto &dirName: pathList) {
            if (currentDir.dirItemMap.find(dirName + '/') == currentDir.dirItemMap.end()) {
                return -1;
            }
        }
        return currentDir.dirItemMap[pathList.back()];
    }

    Dir GetDirFromAddress(int address) {
        file->seekg(address * BLOCK_SIZE);
        char buffer[BLOCK_SIZE];
        file->read(buffer, BLOCK_SIZE);
        return Dir(std::string(buffer));
    }

    std::vector<std::string> Split(const std::string &str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::vector<int> AllocateBlock(int blockNum) {
        std::vector<int> blockList;
        for (int i = 0; i < BLOCK_COUNT; i++) {
            if (fileAllocationTable[i] == -1) {
                blockList.push_back(i);
                if (blockList.size() == blockNum) {
                    break;
                }
            }
        }
        if (blockList.size() < blockNum) {
            throw std::runtime_error("no enough free block");
        }
        return blockList;
    }

    void FreeBlock(std::vector<int> blockIndexList) {
        for (int blockIndex: blockIndexList) {
            fileAllocationTable[blockIndex] = -1;
            freeBlock.push_back(blockIndex);
        }
    }

    void MakeDir(const std::string &path){
        std::vector<std::string> pathList = Split(path, '/');
        Dir currentDir = rootDir;
        for (const auto &dirName: pathList) {
            if (currentDir.dirItemMap.find(dirName + '/') == currentDir.dirItemMap.end()) {
                int address = AllocateBlock(1)[0];
                currentDir.AddDirItem(dirName + '/', address);
                currentDir = GetDirFromAddress(address);
            }
        }
    }
};


