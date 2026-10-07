#!/usr/bin/env python3
import argparse
import ftplib
from pathlib import Path

def ensure_dir(ftp, path):
    cur = ""
    for part in path.strip("/").split("/"):
        cur += "/" + part
        try:
            ftp.mkd(cur)
        except ftplib.error_perm:
            pass

def upload_tree(ftp, local, remote):
    ensure_dir(ftp, remote)
    for p in Path(local).rglob("*"):
        rel = p.relative_to(local).as_posix()
        dst = remote.rstrip("/") + "/" + rel
        if p.is_dir():
            ensure_dir(ftp, dst)
        else:
            ensure_dir(ftp, dst.rsplit("/",1)[0])
            with p.open("rb") as f:
                ftp.storbinary("STOR " + dst, f)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("host")
    ap.add_argument("folder")
    ap.add_argument("--port", type=int, default=2121)
    ap.add_argument("--remote", default="/data/homebrew/PPSA99555")
    args = ap.parse_args()
    with ftplib.FTP() as ftp:
        ftp.connect(args.host, args.port, timeout=15)
        ftp.login()
        upload_tree(ftp, Path(args.folder), args.remote)
    print("Uploaded to", args.remote)

if __name__ == "__main__":
    main()
