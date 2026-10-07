#pragma once
#include <cstdint>

namespace psp5 {
struct PadState { std::uint32_t buttons = 0; float lx = 0; float ly = 0; };
class Platform {
public:
    virtual ~Platform() = default;
    virtual PadState pollPad() = 0;
    virtual void present() = 0;
};
}
