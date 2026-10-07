# PSP5 PS5 package layout

This folder mirrors the native-title deployment convention used by ProsperoEden.

Target layout after a successful PS5 build:

```
PPSA99555/
├── eboot.bin
├── sce_sys/
│   └── param.json
└── data/
    └── psp/
        ├── ISO/
        └── GAME/
```

Copy the completed `PPSA99555` folder to:

```
/data/homebrew/PPSA99555
```

using the FTP server provided by the jailbreak/homebrew environment.

Important: the repository does not yet produce a real PS5 `eboot.bin`. The emulator core must first
be linked against a compatible PS5 native-app runtime/toolchain (such as the foundation used by
ProsperoEden). Do not rename a host executable to `eboot.bin`; it will not become a PS5 executable.
