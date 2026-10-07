#pragma once
#include "core/Memory.h"
#include <array>
#include <cstdint>
#include <string>
namespace psp5 {
class Cpu {
public:
 explicit Cpu(Memory& memory): memory_(memory) { reset(); }
 void reset(std::uint32_t entry=0);
 bool step();
 std::uint32_t pc() const { return pc_; }
 std::uint32_t reg(unsigned i) const { return gpr_[i & 31]; }
 void setReg(unsigned i,std::uint32_t v){ if((i&31)!=0) gpr_[i&31]=v; }
 const std::string& lastError() const { return error_; }
private:
 bool fetch32(std::uint32_t addr,std::uint32_t& out) const;
 void branch(std::uint32_t target);
 Memory& memory_;
 std::array<std::uint32_t,32> gpr_{};
 std::uint32_t hi_=0,lo_=0,pc_=0,nextPc_=4;
 std::string error_;
};
}
