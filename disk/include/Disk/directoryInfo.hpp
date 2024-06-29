//
// Created by HeChu on 24-6-29.
//

#ifndef FILESYSTEM_DIRECTORYINFO_HPP
#define FILESYSTEM_DIRECTORYINFO_HPP

#include <map>
#include <string>

class DirectoryInfo {
private:
    std::map<std::string,int> itemMap;

public:
    DirectoryInfo();
};
#endif //FILESYSTEM_DIRECTORYINFO_HPP
