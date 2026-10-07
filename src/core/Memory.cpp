#include "core/Memory.h"
#include <cstring>
namespace psp5 {
Memory::Memory():ram_(kRamSize,0){}
bool Memory::offset(std::uint32_t a,std::size_t n,std::size_t& o) const{
 const auto p=a&0x1fffffffu;
 if(p<kRamBase) return false; o=p-kRamBase; return o<=ram_.size()&&n<=ram_.size()-o;
}
bool Memory::write(std::uint32_t a,const void* d,std::size_t n){std::size_t o;if(!offset(a,n,o))return false;std::memcpy(ram_.data()+o,d,n);return true;}
bool Memory::read(std::uint32_t a,void* d,std::size_t n)const{std::size_t o;if(!offset(a,n,o))return false;std::memcpy(d,ram_.data()+o,n);return true;}
bool Memory::read32(std::uint32_t a,std::uint32_t& v)const{std::uint8_t b[4];if(!read(a,b,4))return false;v=b[0]|(b[1]<<8)|(b[2]<<16)|(b[3]<<24);return true;}
bool Memory::write32(std::uint32_t a,std::uint32_t v){std::uint8_t b[4]={(std::uint8_t)v,(std::uint8_t)(v>>8),(std::uint8_t)(v>>16),(std::uint8_t)(v>>24)};return write(a,b,4);}
}
