#include "core/Emulator.h"
#include "core/Cpu.h"
#include <exception>
namespace psp5 {
BootResult Emulator::boot(const std::string& path){
 try{auto image=loader_.load(path,memory_);entry_=image.entry;booted_=true;return{true,"Loaded ELF; entry=0x"+hex(entry_)};}
 catch(const std::exception&e){return{false,e.what()};}
}
int Emulator::run(){
 if(!booted_)return 1; Cpu cpu(memory_);cpu.reset(entry_);
 constexpr unsigned kBudget=1000000;
 for(unsigned i=0;i<kBudget;i++) if(!cpu.step()) return 2;
 return 0;
}
std::string Emulator::hex(std::uint32_t v){const char*d="0123456789ABCDEF";std::string s(8,'0');for(int i=7;i>=0;--i){s[i]=d[v&15];v>>=4;}return s;}
}
