# TriExporter

A Windows C++ application for processing and visualizing EVE Online 3D model files (.tri format). This fork of the [original TriExporter](https://triexporter.codeplex.com/) adds support for EVE Online's shared resource cache system.

## ⚠️ Important Notice

**This project uses severely outdated dependencies (DirectX SDK 2010, FBX SDK 2013.3) that contain known security vulnerabilities. See [ANALYSIS.md](ANALYSIS.md) and [MODERNIZATION_PLAN.md](MODERNIZATION_PLAN.md) for detailed upgrade recommendations.**

## Features

- **3D Model Visualization**: View EVE Online .tri model files in a 3D environment
- **Shared Resource Cache**: Support for EVE Online's shared resource cache system
- **Multiple Export Formats**: Export to various 3D file formats via FBX SDK
- **Texture Support**: Handle multiple texture formats through DevIL library
- **Interactive GUI**: Windows-native interface with 3D viewport controls

## System Requirements

### Runtime Requirements
- Windows 10/11 (x64 recommended)
- DirectX 11 compatible graphics card
- 4GB RAM minimum, 8GB recommended

### Build Requirements
- Visual Studio 2019/2022 Community or higher
- Windows SDK 10.0.22621.0 or later
- FBX SDK 2020.3.4 or later (requires free Autodesk registration)
- CMake 3.20+ (recommended for modern builds)

## Quick Start

### Option 1: Visual Studio (Current)
1. Install build dependencies (see below)
2. Open `TriExporter.sln` in Visual Studio
3. Set configuration to Release/x64
4. Build solution (Ctrl+Shift+B)

### Option 2: CMake (Recommended - Coming Soon)
```bash
git clone https://github.com/AlleyKatPr0/triexporter.git
cd triexporter
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

## Installation & Setup

### 1. Install Dependencies

#### FBX SDK
1. Register at [Autodesk Developer Center](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-3-4)
2. Download FBX SDK 2020.3.4 for Visual Studio 2019
3. Install to default location: `C:\Program Files\Autodesk\FBX\FBX SDK\2020.3.4`

#### DirectX (Windows SDK)
- Install Windows SDK 10.0.22621.0 or later from [Microsoft](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
- DirectX components are included in modern Windows SDK

### 2. Configure Build Environment
1. Update `dxsdk.props` and `fbxsdk.props` with your SDK installation paths
2. Ensure Visual Studio has C++ desktop development workload installed

### 3. Build Process
1. Clone repository: `git clone https://github.com/AlleyKatPr0/triexporter.git`
2. Open `TriExporter.sln` in Visual Studio
3. Select Release configuration (recommended)
4. Build → Build Solution (F7)
5. Executable will be in `bin/Release/TriExporter.exe`

## Usage

### Basic Operation
1. Launch TriExporter.exe
2. File → Open to load a .tri model file
3. Use mouse controls to navigate 3D view:
   - **Left Click + Drag**: Rotate view
   - **Right Click + Drag**: Pan
   - **Mouse Wheel**: Zoom
4. Adjust lighting and scale with provided controls
5. Export via File → Export (requires proper FBX SDK setup)

### Working with EVE Online Data
1. Extract .tri files from EVE Online installation
2. Configure shared resource cache path in registry:
   - Key: `HKEY_CURRENT_USER\SOFTWARE\CCP\EVEONLINE`
   - Value: `CACHEFOLDER` = path to EVE cache directory
3. Load models through TriExporter interface

## Project Structure

```
triexporter/
├── TriExporter/          # Main application source
│   ├── MainDlg.cpp/h    # Main dialog and UI logic
│   ├── TriFile.cpp/h    # .tri file format handling
│   └── 3d.cpp/h         # 3D rendering engine
├── triexporter/          # Shared cache functionality
│   ├── SharedCache.cpp/h # EVE Online cache integration
│   └── UnstuffDlg.h     # Cache extraction dialog
├── DevIL/               # Image processing library
├── libpng/              # PNG image support
├── zlib/                # Compression library
├── lib3ds/              # 3DS file format support
├── grannystuff/         # Granny 3D SDK headers
└── WTL/                 # Windows Template Library
```

## Contributing

We welcome contributions! Please read our guidelines:

1. **Security First**: Help modernize outdated dependencies
2. **Code Style**: Follow existing patterns, consider modern C++ practices
3. **Documentation**: Update documentation for any changes
4. **Testing**: Test with actual EVE Online data when possible

### Development Priorities
1. **Critical**: Update DirectX and FBX SDK dependencies ([See Analysis](ANALYSIS.md))
2. **High**: Implement CMake build system
3. **Medium**: Add unit tests and CI/CD
4. **Low**: Code modernization and cross-platform support

## Known Issues

- ⚠️ **Security**: Uses vulnerable DirectX SDK 2010 and FBX SDK 2013.3
- **Build**: Hard-coded paths in .props files may need adjustment
- **Compatibility**: May not work correctly on Windows 11 without updates
- **Dependencies**: Some third-party libraries are very outdated

## Documentation

- **[ANALYSIS.md](ANALYSIS.md)**: Comprehensive codebase analysis and recommendations
- **[MODERNIZATION_PLAN.md](MODERNIZATION_PLAN.md)**: Detailed upgrade implementation plan
- **Build Logs**: Check Visual Studio output for specific build issues

## License

This project maintains the same license as the original TriExporter from CodePlex. Please refer to original project documentation for specific licensing terms.

## Support & Community

- **Issues**: Report bugs via GitHub Issues
- **Discussions**: General questions and feature requests
- **EVE Community**: Connect with other EVE Online developers and modders

## Acknowledgments

- Original TriExporter team from CodePlex
- EVE Online community for continued interest
- CCP Games for EVE Online
- Contributors to supporting libraries (DevIL, libpng, zlib, lib3ds)

---

**⚡ Quick Links:**
- [View Analysis](ANALYSIS.md) - Detailed codebase analysis
- [Modernization Plan](MODERNIZATION_PLAN.md) - Upgrade roadmap  
- [Issues](../../issues) - Report problems
- [Discussions](../../discussions) - Ask questions

*Last updated: 2024 - This fork is actively seeking maintainers for modernization efforts.*
