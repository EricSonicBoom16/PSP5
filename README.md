# PSP5

Experimental standalone PSP emulator project targeting PlayStation 5 homebrew environments.

> Status: early scaffold. This repository does **not** yet emulate a PSP or provide a production PS5 package.

## Goals
- Clean separation between PSP emulation and PS5-specific platform code.
- Load user-supplied PSP homebrew/game images from local storage.
- Incrementally implement CPU, memory, HLE, graphics, audio, input and filesystem layers.
- Keep platform-specific APIs behind a small interface so the core can be tested on a desktop host.

## Current scaffold
```
src/
  main.cpp
  core/Emulator.*
  core/Memory.*
  loader/PspLoader.*
  platform/Platform.*
docs/
  ARCHITECTURE.md
  AUTHENTICATION.md
```

## Build
A normal CMake host build is supplied for development:

```sh
cmake -S . -B build
cmake --build build
./build/psp5 path/to/file.elf
```

A real PS5 build requires a compatible homebrew SDK/toolchain and platform implementations; those are intentionally isolated from the portable core.

## ROMs and firmware
No Sony firmware, keys, games, or copyrighted PSP system files are included. Use software you are legally entitled to use.

## Authentication
PSP5 currently has no accounts, cloud backend, OAuth flow, API keys, or bearer tokens. See [docs/AUTHENTICATION.md](docs/AUTHENTICATION.md).

## License
GPL-3.0.
