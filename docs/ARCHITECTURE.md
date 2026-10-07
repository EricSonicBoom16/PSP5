# PSP5 architecture

PSP5 is split into a portable emulation core and a platform backend.

## Request / execution flow
1. `main` receives a local executable path.
2. `Emulator::boot` asks `PspLoader` to validate/load it.
3. The loader currently recognizes ELF magic only.
4. Future ELF program headers will map segments into `Memory`.
5. A future Allegrex CPU core will execute guest instructions.
6. HLE will translate supported PSP kernel/syscall operations.
7. GPU/audio/input calls will pass through platform abstractions.
8. A PS5 backend will translate those abstractions to the selected homebrew SDK.

## Planned core components
- Allegrex/MIPS CPU interpreter first; optional JIT later.
- PSP memory map and MMIO.
- ELF/PBP/ISO/CSO loading.
- Kernel/HLE modules and syscall dispatch.
- GE graphics command processing.
- Audio mixer.
- Controller mapping.
- Virtual Memory Stick filesystem.
- Save-state/configuration layer.

The current repository is a foundation, not a functioning PSP emulator.
