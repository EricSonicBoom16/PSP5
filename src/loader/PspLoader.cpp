#include "loader/PspLoader.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace psp5 {
LoadedImage PspLoader::load(const std::string& path) const {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("cannot open input file");
    LoadedImage image;
    image.path = path;
    image.bytes.assign(std::istreambuf_iterator<char>(in), {});
    image.isElf = image.bytes.size() >= 4 &&
        image.bytes[0] == 0x7f && image.bytes[1] == 'E' &&
        image.bytes[2] == 'L' && image.bytes[3] == 'F';
    if (!image.isElf)
        throw std::runtime_error("scaffold currently accepts ELF input only");
    return image;
}
}
