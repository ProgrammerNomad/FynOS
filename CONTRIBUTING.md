# Contributing to FynOS

Thank you for your interest in FynOS. This project follows strict architectural discipline to grow from a 512-byte bootloader into a full desktop OS.

## Before You Code

1. Read [`docs/philosophy.md`](docs/philosophy.md)
2. Read [`docs/coding-standard.md`](docs/coding-standard.md)
3. Find or create the relevant doc in [`docs/architecture/`](docs/architecture/)
4. Open a GitHub Issue linked to the appropriate Milestone (M0-M8)

**Never code before the architecture doc for that subsystem exists** (even as a draft).

## Development Environment

Linux/WSL is the **only** supported development platform:

```bash
# Windows users: use WSL Ubuntu
sudo apt install nasm qemu-system-x86 build-essential gcc-multilib
cd /path/to/FynOS
make
make run
```

No `build.bat`. No PowerShell build scripts. One Makefile.

## Workflow

1. Fork and clone the repo
2. Create a feature branch (`feat/keyboard`, `feat/vfs`, etc.)
3. Write or update the architecture doc for your subsystem
4. Implement with paired `.c`/`.h` modules
5. Verify `make && make run` - every release must boot
6. Submit a PR referencing the architecture doc section

## Pull Request Checklist

- [ ] Architecture doc updated or created
- [ ] Code follows [`docs/coding-standard.md`](docs/coding-standard.md)
- [ ] `make` completes with zero warnings (`-Werror`)
- [ ] `make run` boots successfully in QEMU
- [ ] No new global variables without justification
- [ ] Layer boundaries respected (see philosophy doc)

## Milestones

| Milestone | Scope |
|-----------|-------|
| M0 | Bootloader |
| M1 | C Kernel |
| M2 | Memory |
| M3 | Keyboard |
| M4 | Shell |
| M5 | Filesystem |
| M6 | Graphics |
| M7 | GUI (userspace) |
| M8 | Networking |

## Questions

Open a GitHub Issue for design questions. Reference the relevant `docs/architecture/*.md` file.
