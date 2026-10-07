#include "demo_renderer.hpp"

namespace {
void draw_psp5(ps5::demo::Canvas& canvas) noexcept {
    using ps5::demo::Color;
    canvas.clear(Color::background);
    canvas.text(160, 170, "PSP5", 22, Color::white);
    canvas.text(165, 390, "GCModz", 8, Color::cyan);
    canvas.rectangle(160, 520, 1600, 8, Color::white);
    canvas.text(160, 620, "NATIVE PS5 BOOT OK", 7, Color::white);
    canvas.text(160, 760, "PSP EMULATOR CORE NEXT", 6, Color::magenta);
}
}
int main() {
    ps5::demo::run(draw_psp5, "PSP5 native bootstrap running");
}
