#pragma once
#include "core/Memory.h"
#include "loader/PspLoader.h"
#include <cstdint>
#include <string>
namespace psp5 {
struct BootResult{bool ok;std::string message;};
class Emulator{
public: BootResult boot(const std::string& path);int run();
private: static std::string hex(std::uint32_t);Memory memory_;PspLoader loader_;bool booted_=false;std::uint32_t entry_=0;
};
}
