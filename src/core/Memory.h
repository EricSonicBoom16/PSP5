#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace psp5 {
class Memory {
public:
 static constexpr std::uint32_t kRamBase=0x08000000u;
 static constexpr std::size_t kRamSize=32u*1024u*1024u;
 Memory();
 bool write(std::uint32_t address,const void* data,std::size_t size);
 bool read(std::uint32_t address,void* data,std::size_t size) const;
 bool read32(std::uint32_t address,std::uint32_t& value) const;
 bool write32(std::uint32_t address,std::uint32_t value);
 std::size_t size() const{return ram_.size();}
private:
 bool offset(std::uint32_t address,std::size_t size,std::size_t& out) const;
 std::vector<std::uint8_t> ram_;
};
}
