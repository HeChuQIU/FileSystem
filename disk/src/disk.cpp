//
// Created by HeChu on 24-6-28.
//

#include <vector>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <sstream>
#include "Disk/fileControlBlock.hpp"

class Disk {
private:
    int blockNum;
    std::vector<char> bitmap;
    std::fstream file;
    int rootDirAddr = 1;

public:
    Disk(int blockNum, std::fstream &&file) : file(std::move(file)) {
        if (blockNum <= 0) {
            throw std::invalid_argument("blockSize and blockNum must be positive");
        }
        if (blockNum % 8 != 0) {
            throw std::invalid_argument("blockSize must be a multiple of 8");
        }
        auto maxBlockNum = BlockSizeByByte() - sizeof(blockNum) - bitmap.size();
        if (blockNum > maxBlockNum) {
            throw std::invalid_argument("blockNum can't be larger than " + std::to_string(maxBlockNum));
        }

        this->blockNum = blockNum;
        this->bitmap = std::vector<char>(blockNum / 8, 0);
    }

    Disk(std::fstream &&file) : file(std::move(file)) {
        file.read(reinterpret_cast<char *>(&blockNum), sizeof(blockNum));
        bitmap = std::vector<char>(blockNum / 8, 0);
        file.read(bitmap.data(), bitmap.size());
    }

    ~Disk() {
        file.close();
    }

    // 序列化这个实例的信息
    std::stringstream Serialize() {
        std::stringstream data;
        data.write(reinterpret_cast<char *>(&blockNum), sizeof(blockNum));
        data.write(bitmap.data(), bitmap.size());
        return data;
    }

    static int BlockSizeByByte() {
        return 1024;
    }

    int BlockNum() {
        return blockNum;
    }

    void WriteBlock(int blockAddr, std::stringstream data) {
        if (blockAddr < 0 || blockAddr >= blockNum) {
            throw std::invalid_argument("blockAddr out of range");
        }
        if (data.str().size() > BlockSizeByByte()) {
            throw std::invalid_argument("data too large");
        }

        file.seekp(blockAddr * BlockSizeByByte());
        file << data.rdbuf();
        file.flush();
    }

    std::stringstream ReadBlock(int blockAddr) {
        if (blockAddr < 0 || blockAddr >= blockNum) {
            throw std::invalid_argument("blockAddr out of range");
        }

        file.seekg(blockAddr * BlockSizeByByte());
        std::vector<char> buffer(BlockSizeByByte());
        file.read(buffer.data(), BlockSizeByByte());

        std::stringstream data;
        data.write(buffer.data(), BlockSizeByByte());
        return data;
    }

    std::shared_ptr<FileControlBlock> RootDir(){
        FileControlBlock(ReadBlock(rootDirAddr));
    }

    static bool IsValidUserName(const std::string &userName) {
        return userName.size() <= 8;
    }

    static bool IsValidFileOrDirName(const std::string &name) {
        return name.size() <= 8;
    }

    static int MaxFileNumberInDir() {
        return BlockSizeByByte() / (8 + sizeof(int)) - 2;
    }

    static int MaxFileSizeOf(IndirectFlag indirectFlag) {
        int maxAddrInBlock = BlockSizeByByte() / sizeof(int);
        switch (indirectFlag) {
            case IndirectFlag::DIRECT:
                return 10 * BlockSizeByByte();
            case IndirectFlag::INDIRECT:
                return BlockSizeByByte() * maxAddrInBlock;
            case IndirectFlag::DOUBLE_INDIRECT:
                return BlockSizeByByte() * maxAddrInBlock * maxAddrInBlock;
            case IndirectFlag::TRIPLE_INDIRECT:
                return BlockSizeByByte() * maxAddrInBlock * maxAddrInBlock * maxAddrInBlock;
        }
    }
};