#!/usr/bin/env python3
import shutil
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "build" / "ps5" / "PPSA99555"

def main():
    if OUT.exists():
        shutil.rmtree(OUT)
    (OUT / "sce_sys").mkdir(parents=True)
    (OUT / "data" / "psp" / "ISO").mkdir(parents=True)
    (OUT / "data" / "psp" / "GAME").mkdir(parents=True)
    shutil.copy2(ROOT / "ps5" / "sce_sys" / "param.json", OUT / "sce_sys" / "param.json")
    readme = OUT / "README.txt"
    readme.write_text(
        "PSP5 package scaffold.\n"
        "A real PS5 eboot.bin is not generated yet.\n"
        "Do not FTP this folder expecting it to launch until eboot.bin is built.\n",
        encoding="utf-8"
    )
    print(OUT)

if __name__ == "__main__":
    main()
