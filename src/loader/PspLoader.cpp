#include "loader/PspLoader.h"
#include "loader/Elf32.h"
#include <cstring>
#include <fstream>
#include <iterator>
#include <stdexcept>
namespace psp5 {
LoadedImage PspLoader::load(const std::string& path,Memory& mem)const{
 std::ifstream in(path,std::ios::binary); if(!in)throw std::runtime_error("cannot open input");
 LoadedImage x; x.path=path;x.bytes.assign(std::istreambuf_iterator<char>(in),{});
 if(x.bytes.size()<sizeof(Elf32Ehdr))throw std::runtime_error("file too small");
 Elf32Ehdr h{};std::memcpy(&h,x.bytes.data(),sizeof h);
 x.isElf=h.ident[0]==0x7f&&h.ident[1]=='E'&&h.ident[2]=='L'&&h.ident[3]=='F';
 if(!x.isElf||h.ident[4]!=1||h.ident[5]!=1)throw std::runtime_error("expected 32-bit little-endian ELF");
 if(h.phentsize!=sizeof(Elf32Phdr))throw std::runtime_error("unsupported program-header size");
 for(unsigned i=0;i<h.phnum;i++){
  const std::size_t po=h.phoff+i*sizeof(Elf32Phdr); if(po+sizeof(Elf32Phdr)>x.bytes.size())throw std::runtime_error("bad program headers");
  Elf32Phdr p{};std::memcpy(&p,x.bytes.data()+po,sizeof p); if(p.type!=PT_LOAD)continue;
  if(p.offset+p.filesz>x.bytes.size()||p.memsz<p.filesz)throw std::runtime_error("bad load segment");
  if(!mem.write(p.vaddr,x.bytes.data()+p.offset,p.filesz))throw std::runtime_error("segment outside PSP RAM");
  std::vector<std::uint8_t> zero(p.memsz-p.filesz); if(!zero.empty()&&!mem.write(p.vaddr+p.filesz,zero.data(),zero.size()))throw std::runtime_error("BSS outside PSP RAM");
 }
 x.entry=h.entry; return x;
}
}
