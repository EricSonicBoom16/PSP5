# Native PS5 bootstrap

PSP5 follows the native-title pipeline used by ProsperoEden: cross-compile for `x86_64-sie-ps5`, link a native PIE, convert it with `ps5-native-tool`, create `eboot.bin`, and bundle `sce_module/libc.prx` plus `sce_sys/param.json`.

Required environment variables: `PS5_PAYLOAD_SDK`, `PS5_NATIVE_BOILERPLATE`, and `PS5_NATIVE_TOOL`.

```bash
bash tools/build-ps5-native.sh
python3 tools/install-ftp.py <PS5-IP> build/ps5/PPSA99555 --port 2121
```

Target install path: `/data/homebrew/PPSA99555`.

The current target is a native bootstrap. A successful build proves the PS5 application pipeline; PSP emulation is integrated afterward.
