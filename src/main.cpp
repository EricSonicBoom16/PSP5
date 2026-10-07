#include "core/Emulator.h"
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "PSP5 experimental emulator scaffold\n";
    if (argc != 2) {
        std::cout << "Usage: psp5 <PSP ELF>\n";
        return 0;
    }

    psp5::Emulator emulator;
    const auto result = emulator.boot(argv[1]);
    if (!result.ok) {
        std::cerr << "Boot failed: " << result.message << "\n";
        return 1;
    }
    std::cout << result.message << "\n";
    return emulator.run();
}
