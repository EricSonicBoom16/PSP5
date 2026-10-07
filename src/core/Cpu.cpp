#include "core/Cpu.h"
#include <cstring>
namespace psp5 {
static std::int32_t sx16(std::uint32_t x){ return static_cast<std::int16_t>(x); }
void Cpu::reset(std::uint32_t entry){ gpr_.fill(0); hi_=lo_=0; pc_=entry; nextPc_=entry+4; error_.clear(); }
bool Cpu::fetch32(std::uint32_t a,std::uint32_t& o) const { return memory_.read32(a,o); }
void Cpu::branch(std::uint32_t target){ nextPc_=target; }
bool Cpu::step(){
 std::uint32_t ins=0; if(!fetch32(pc_,ins)){ error_="instruction fetch fault"; return false; }
 const std::uint32_t curNext=nextPc_; nextPc_+=4;
 const auto op=ins>>26, rs=(ins>>21)&31, rt=(ins>>16)&31, rd=(ins>>11)&31, sa=(ins>>6)&31, fn=ins&63;
 const auto imm=ins&0xffffu;
 auto wr=[&](unsigned n,std::uint32_t v){ if(n) gpr_[n]=v; };
 switch(op){
 case 0:
  switch(fn){
   case 0x00: wr(rd,gpr_[rt]<<sa); break;
   case 0x02: wr(rd,gpr_[rt]>>sa); break;
   case 0x03: wr(rd,static_cast<std::uint32_t>(static_cast<std::int32_t>(gpr_[rt])>>sa)); break;
   case 0x08: branch(gpr_[rs]); break;
   case 0x09: wr(rd?rd:31,nextPc_); branch(gpr_[rs]); break;
   case 0x20: case 0x21: wr(rd,gpr_[rs]+gpr_[rt]); break;
   case 0x22: case 0x23: wr(rd,gpr_[rs]-gpr_[rt]); break;
   case 0x24: wr(rd,gpr_[rs]&gpr_[rt]); break;
   case 0x25: wr(rd,gpr_[rs]|gpr_[rt]); break;
   case 0x26: wr(rd,gpr_[rs]^gpr_[rt]); break;
   case 0x27: wr(rd,~(gpr_[rs]|gpr_[rt])); break;
   case 0x2a: wr(rd,static_cast<std::int32_t>(gpr_[rs])<static_cast<std::int32_t>(gpr_[rt])); break;
   case 0x2b: wr(rd,gpr_[rs]<gpr_[rt]); break;
   default: error_="unimplemented SPECIAL opcode"; return false;
  } break;
 case 0x02: branch((curNext&0xf0000000u)|((ins&0x03ffffffu)<<2)); break;
 case 0x03: wr(31,nextPc_); branch((curNext&0xf0000000u)|((ins&0x03ffffffu)<<2)); break;
 case 0x04: if(gpr_[rs]==gpr_[rt]) branch(curNext+(sx16(imm)<<2)); break;
 case 0x05: if(gpr_[rs]!=gpr_[rt]) branch(curNext+(sx16(imm)<<2)); break;
 case 0x08: case 0x09: wr(rt,gpr_[rs]+static_cast<std::uint32_t>(sx16(imm))); break;
 case 0x0a: wr(rt,static_cast<std::int32_t>(gpr_[rs])<sx16(imm)); break;
 case 0x0b: wr(rt,gpr_[rs]<static_cast<std::uint32_t>(sx16(imm))); break;
 case 0x0c: wr(rt,gpr_[rs]&imm); break;
 case 0x0d: wr(rt,gpr_[rs]|imm); break;
 case 0x0e: wr(rt,gpr_[rs]^imm); break;
 case 0x0f: wr(rt,imm<<16); break;
 case 0x23: { std::uint32_t v; if(!memory_.read32(gpr_[rs]+sx16(imm),v)){error_="lw fault";return false;} wr(rt,v); } break;
 case 0x2b: if(!memory_.write32(gpr_[rs]+sx16(imm),gpr_[rt])){error_="sw fault";return false;} break;
 default: error_="unimplemented primary opcode"; return false;
 }
 gpr_[0]=0; pc_=curNext; return true;
}
}
