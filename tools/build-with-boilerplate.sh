#!/usr/bin/env bash
set -euo pipefail
root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
work="${PSP5_BOILERPLATE_DIR:-$root/.deps/ps5-native-app-boilerplate}"
commit=dd44bbdc75437332ed22e3ba95126733419ef25a

if [[ ! -d "$work/.git" ]]; then
  mkdir -p "$(dirname "$work")"
  git clone https://github.com/blackbearreloaded/ps5-native-app-boilerplate.git "$work"
fi
git -C "$work" fetch origin "$commit" --depth=1
git -C "$work" checkout --detach "$commit"

rm -rf "$work/psp5-src" "$work/psp5-sce-sys"
mkdir -p "$work/psp5-src" "$work/psp5-sce-sys"
cp "$root/ps5/src/main.cpp" "$work/psp5-src/main.cpp"
cp "$root/ps5/sce_sys/param.json" "$work/psp5-sce-sys/param.json"
# Until PSP5 has final branded artwork, reuse the boilerplate's known-good required PS5 assets.
cp "$work/sce_sys/icon0.png" "$work/psp5-sce-sys/icon0.png"
cp "$work/sce_sys/pic0.dds" "$work/psp5-sce-sys/pic0.dds"
cp "$work/sce_sys/pic1.dds" "$work/psp5-sce-sys/pic1.dds"
cp "$work/sce_sys/snd0.at9" "$work/psp5-sce-sys/snd0.at9"

make -C "$work"   APP_SOURCE_DIR=psp5-src   APP_PARAM=psp5-sce-sys/param.json   APP_SCE_SYS=psp5-sce-sys   APP_ASSETS=

rm -rf "$root/build/ps5/PPSA99555"
mkdir -p "$root/build/ps5"
cp -a "$work/dist/PPSA99555" "$root/build/ps5/PPSA99555"
echo "PSP5 native title folder: $root/build/ps5/PPSA99555"
