# Repository Agent Instructions

- Run `yamllint .github/workflows/*.yml` after modifying any workflow files.
- Ensure code builds with MSBuild or Visual Studio; the CI workflow uses `.github/workflows/build.yml` as reference.
- No automated tests currently exist; add and run tests when available.
- Prefer modern C++ features (RAII, smart pointers) and plan for Windows 11 UI updates (e.g., WinUI 3).
- Keep commits focused and reference relevant tickets or issues in commit messages.
