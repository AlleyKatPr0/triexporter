# TriExporter Migration Guide

This document outlines the next steps for modernizing the TriExporter codebase.

## Overview

The TriExporter project is being modernized to:
- Remove vendor dependencies and use vcpkg for package management
- Migrate from MSBuild-only to CMake + vcpkg build system
- Improve code quality with modern tooling
- Add continuous integration

## Current State

- **Build System**: Visual Studio MSBuild solution with vendored dependencies
- **Dependencies**: DevIL, libpng, zlib, WTL, lib3ds bundled in repository
- **Toolchain**: Visual Studio 2010+ with DirectX SDK

## Migration Plan

### Phase 1: Infrastructure (Current)
- [x] Add vcpkg.json manifest with dependencies
- [x] Add CMakeLists.txt skeleton
- [x] Add code quality configurations (.clang-format, .clang-tidy, .editorconfig)
- [x] Add GitHub Actions CI workflows
- [x] Introduce WIC texture loader to reduce DevIL dependency

### Phase 2: Source Migration (Future PRs)
- [ ] Migrate source files to `src/` directory structure
- [ ] Update CMakeLists.txt to build actual targets
- [ ] Remove vendored dependencies (DevIL, libpng, zlib, lib3ds)
- [ ] Update include paths and dependencies

### Phase 3: Cleanup (Future PRs)
- [ ] Remove MSBuild solution files (after CMake migration is complete)
- [ ] Remove vendor directories
- [ ] Update documentation

## Dependencies

The following dependencies are defined in vcpkg.json:
- **assimp**: 3D model loading (replacement for lib3ds)
- **libpng**: PNG image support
- **zlib**: Compression library
- **wtl**: Windows Template Library
- **stb**: Header-only libraries for image processing
- **fmt**: Modern C++ string formatting
- **spdlog**: Fast C++ logging library

## Build Instructions

### Current MSBuild (Stable)
```bash
# Open in Visual Studio
TriExporter.sln

# Or use MSBuild command line
msbuild TriExporter.sln /p:Configuration=Release /p:Platform=Win32
```

### Future CMake + vcpkg (Work in Progress)
```bash
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.bat

# Configure and build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

## Code Quality

### Formatting
```bash
clang-format -i **/*.cpp **/*.h
```

### Static Analysis
```bash
clang-tidy **/*.cpp -- -I./include
```

## Licensing Hygiene

When migrating code, ensure:
1. All third-party code is properly attributed
2. License compatibility is maintained
3. Copyright notices are preserved
4. Vendor code removal is done cleanly

## Notes

- Keep MSBuild solution working during transition
- Test both build systems in parallel
- Maintain backward compatibility where possible
- Document breaking changes clearly