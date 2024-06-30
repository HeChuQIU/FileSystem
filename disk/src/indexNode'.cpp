//
// Created by HeChu on 24-6-30.
//

#include <string>

class IndexNode {
private:
    int fileLength;
    int fileAddress;
    char permission[2]; // 用户/其他 _rwx_rwx
    std::string owner;
public:
    IndexNode() = default;

    IndexNode(int fileLength, int fileAddress, const char permission[2], std::string owner) :
            fileLength(fileLength),
            fileAddress(fileAddress),
            owner(std::move(owner)) {
        this->permission[0] = permission[0];
        this->permission[1] = permission[1];
    }

    IndexNode(std::string &stream) {
        int offset = 0;
        fileLength = std::stoi(stream.substr(offset, sizeof(int)));
        offset += sizeof(int);
        fileAddress = std::stoi(stream.substr(offset, sizeof(int)));
        offset += sizeof(int);
        permission[0] = stream[offset];
        offset += sizeof(char);
        permission[1] = stream[offset];
        offset += sizeof(char);
        owner = stream.substr(offset, 16);
    }

    std::string Serialize() {
        std::string stream;
        stream += std::to_string(fileLength);
        stream += std::to_string(fileAddress);
        stream += permission[0];
        stream += permission[1];
        stream += owner;
        return stream;
    }
};