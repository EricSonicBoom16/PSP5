#!/usr/bin/env bash
set -euo pipefail
root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
sdk=${PS5_PAYLOAD_SDK:?Set PS5_PAYLOAD_SDK}
boilerplate=${PS5_NATIVE_BOILERPLATE:?Set PS5_NATIVE_BOILERPLATE}
builder=${PS5_NATIVE_TOOL:?Set PS5_NATIVE_TOOL}
build="$root/build/ps5-native"
app="$root/build/ps5/PPSA99555"
cmake -S "$root/ps5" -B "$build" -G Ninja -DCMAKE_TOOLCHAIN_FILE="$root/ps5/toolchain.cmake"
cmake --build "$build"
mkdir -p "$app/sce_sys" "$app/sce_module"
cp "$root/ps5/sce_sys/param.json" "$app/sce_sys/param.json"
cp "$boilerplate/runtime/libc.prx" "$app/sce_module/libc.prx"
lld="$boilerplate/.deps/native/ps5-payload-sdk/bin/prospero-lld"
"$lld" -L "$sdk/target/lib" -T "$boilerplate/tooling/native/ps5-pie.ld" -e _start -o "$build/psp5-pie.elf" "$build/CMakeFiles/psp5-native.dir/src/main.cpp.o" --start-group "$sdk/target/lib/libc++.a" "$sdk/target/lib/libc++abi.a" "$sdk/target/lib/libunwind.a" --end-group --as-needed "$sdk/target/lib/libSceLibcInternal.so" "$sdk/target/lib/libkernel.so" "$sdk/target/lib/libc.a"
"$builder" link --in "$build/psp5-pie.elf" --out "$build/eboot.elf" --stub-dir "$sdk/target/lib" --module-sdk 0x02000009 --companion-sdk 0x08050001 --file-name eboot.elf
"$builder" self --sign --in "$build/eboot.elf" --out "$app/eboot.bin" --magic 0x1D3D154F
echo "Built: $app"
