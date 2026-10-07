#pragma once
#include <cstdint>
namespace psp5 {
#pragma pack(push,1)
struct Elf32Ehdr{ unsigned char ident[16]; std::uint16_t type,machine; std::uint32_t version,entry,phoff,shoff,flags; std::uint16_t ehsize,phentsize,phnum,shentsize,shnum,shstrndx; };
struct Elf32Phdr{ std::uint32_t type,offset,vaddr,paddr,filesz,memsz,flags,align; };
#pragma pack(pop)
static constexpr std::uint32_t PT_LOAD=1;
}
