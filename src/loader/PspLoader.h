#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace psp5 {
struct LoadedImage {
    std::string path;
    std::vector<std::uint8_t> bytes;
    bool isElf = false;
};
class PspLoader {
public:
    LoadedImage load(const std::string& path) const;
};
}
