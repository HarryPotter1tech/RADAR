## RADAR Vision Location

Repository:

- https://github.com/HarryPotter1tech/alliance_radar_vision_location.git

## Quick Start

```bash
git clone https://github.com/HarryPotter1tech/alliance_radar_vision_location.git
cd alliance_radar_vision_location
./init.sh
cmake -S . -B build
cmake --build build -j
```

## Daily Git Workflow

```bash
git pull --rebase
git add .
git commit -m "your message"
git push
```

## Git Pre-commit Hook (clang-format)

Install once after cloning:

```bash
./scripts/install-git-hooks.sh
```

Behavior:

- On `git commit`, staged C/C++ files are auto-formatted with `clang-format`.
- If any file was reformatted, the hook updates the staged content and rejects the commit once.
- Re-run `git commit` after reviewing formatted changes.

