## Git Pre-commit Hook (clang-format)

Install once after cloning:

```bash
./scripts/install-git-hooks.sh
```

Behavior:

- On `git commit`, staged C/C++ files are auto-formatted with `clang-format-22` (fallback: `clang-format`).
- If any file was reformatted, the hook updates the staged content and rejects the commit once.
- Re-run `git commit` after reviewing formatted changes.

