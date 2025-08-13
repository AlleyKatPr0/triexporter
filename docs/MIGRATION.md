# Modernization Migration Notes

This PR introduces:
- vcpkg.json for dependency management (assimp, libpng, zlib, WTL, stb, fmt, spdlog)
- CMakeLists.txt scaffold
- CI workflows for MSBuild and CMake
- clang-format / clang-tidy configs
- A WIC-based texture loader for Direct3D9

Next steps (incremental):
1. Unvendor and remove directories: `DevIL/`, `ilu/`, `lib3ds/`, `libpng/`, `zlib/`, `WTL/` after replacing their usage with package-managed dependencies.
2. Replace any remaining DevIL image I/O with the included WIC loader or stb_image/stb_image_write.
3. Replace lib3ds with Assimp (`assimp::Importer`) for `.3ds` and other formats.
4. Move application sources into `src/` and headers into `include/` for CMake; update CMake target sources accordingly.
5. Build with CMake + vcpkg toolchain (see `.github/workflows/ci-cmake.yml`).
6. Enforce modern C++ guidelines via clang-tidy and address findings incrementally.

Licensing hygiene:
- Prefer dynamic linking and permissive licenses to avoid static-LGPL issues.