#include "core/Emulator.h"
#include <exception>

namespace psp5 {
BootResult Emulator::boot(const std::string& path) {
    try {
        const auto image = loader_.load(path);
        booted_ = true;
        return {true, "Recognized PSP ELF (" + std::to_string(image.bytes.size()) +
                      " bytes). CPU execution is not implemented yet."};
    } catch (const std::exception& e) {
        return {false, e.what()};
    }
}
int Emulator::run() {
    if (!booted_) return 1;
    // TODO: MIPS Allegrex fetch/decode/execute loop, HLE and devices.
    return 0;
}
}
