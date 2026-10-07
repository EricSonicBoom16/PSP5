#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace psp5 {
class Memory {
public:
    static constexpr std::size_t kRamSize = 32u * 1024u * 1024u;
    Memory();
    bool write(std::uint32_t address, const void* data, std::size_t size);
    bool read(std::uint32_t address, void* data, std::size_t size) const;
    std::size_t size() const { return ram_.size(); }
private:
    std::vector<std::uint8_t> ram_;
};
}
