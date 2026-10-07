#include "core/Memory.h"
#include <cstring>

namespace psp5 {
Memory::Memory() : ram_(kRamSize, 0) {}

bool Memory::write(std::uint32_t address, const void* data, std::size_t size) {
    if (address > ram_.size() || size > ram_.size() - address) return false;
    std::memcpy(ram_.data() + address, data, size);
    return true;
}

bool Memory::read(std::uint32_t address, void* data, std::size_t size) const {
    if (address > ram_.size() || size > ram_.size() - address) return false;
    std::memcpy(data, ram_.data() + address, size);
    return true;
}
}
