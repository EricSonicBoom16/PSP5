#pragma once
#include "core/Memory.h"
#include <cstdint>
#include <string>
#include <vector>
namespace psp5 {
struct LoadedImage{std::string path;std::vector<std::uint8_t> bytes;bool isElf=false;std::uint32_t entry=0;};
class PspLoader{public: LoadedImage load(const std::string& path,Memory& memory) const;};
}
