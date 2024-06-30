//
// Created by HeChu on 24-6-30.
//

#ifndef FILESYSTEM_INDEXNODE_HPP
#define FILESYSTEM_INDEXNODE_HPP

#include <string>

class IndexNode {
private:
    int fileLength;
    int fileAddress;
    char permission[2];// 用户/其他 _rwx_rwx
    std::string owner;
public:
    IndexNode() = default;

    IndexNode(int fileLength, int fileAddress, const char permission[2], std::string owner);
    IndexNode(std::string &stream);
    std::string Serialize();
};

#endif //FILESYSTEM_INDEXNODE_HPP
