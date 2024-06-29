//
// Created by HeChu on 24-6-29.
//

#ifndef FILESYSTEM_INDIRECTFLAG_HPP
#define FILESYSTEM_INDIRECTFLAG_HPP

#include <sstream>

enum IndirectFlag{
    DIRECT = 0,
    INDIRECT = 1,
    DOUBLE_INDIRECT = 2,
    TRIPLE_INDIRECT = 3
};
#endif //FILESYSTEM_INDIRECTFLAG_HPP
