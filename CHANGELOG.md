# TriExporter Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Comprehensive documentation suite (README.md, ANALYSIS.md, MODERNIZATION_PLAN.md)
- Security advisory with detailed vulnerability assessment
- Contributing guidelines for new developers
- Detailed analysis of codebase and improvement recommendations
- Implementation roadmap for modernization efforts

### Security
- Documented critical security vulnerabilities in DirectX SDK 2010
- Identified risks in outdated FBX SDK 2013.3
- Added security best practices documentation
- Created vulnerability reporting guidelines

### Documentation
- Complete rewrite of README.md with usage instructions
- Added project structure overview
- Created installation and setup guides
- Added development environment setup instructions
- Comprehensive API and architecture documentation

### Planned (Next Release)
- CMake build system implementation
- vcpkg dependency management
- GitHub Actions CI/CD pipeline
- Windows SDK migration (replacing DirectX SDK 2010)
- FBX SDK update to latest version

## [v0.5.1.1] - Previous Release

### Added
- Re-added option for saving files
- Support for EVE Online shared resource cache

### Note
- This was the last release before the modernization effort
- Contains the original fork functionality from CodePlex TriExporter

## [Original] - CodePlex TriExporter

### Features (Inherited)
- 3D model visualization for .tri files
- Multiple export format support
- Texture handling through DevIL
- Windows GUI interface
- DirectX-based 3D rendering

### Dependencies (Legacy)
- DirectX SDK June 2010
- FBX SDK 2013.3  
- Visual Studio 2010 project files
- Various graphics libraries (DevIL, libpng, zlib, lib3ds)

## Upgrade Path

### From v0.5.1.1 to Future Versions
1. **Backup current installation** before upgrading
2. **Update dependencies** (Windows SDK, FBX SDK)
3. **Rebuild from source** with modern toolchain
4. **Test functionality** with existing .tri files
5. **Report issues** if compatibility problems occur

### Breaking Changes (Future)
- **Build System**: Visual Studio 2010 project files will be deprecated
- **Dependencies**: DirectX SDK 2010 will be replaced with Windows SDK
- **API Changes**: Some internal APIs may change during modernization
- **File Paths**: Hard-coded paths in configuration will be removed

## Migration Guide

### For Developers
```cpp
// Old pattern (deprecated)
#include <d3dx9.h>  // DirectX SDK 2010

// New pattern (modern Windows SDK)  
#include <d3d11.h>
#include <DirectXMath.h>
```

### For Users
- **Windows 10/11**: Recommended for modern versions
- **Legacy Support**: Windows 7/8.1 support will be phased out
- **File Formats**: Existing .tri files remain compatible
- **Configuration**: Settings location may change in future versions

## Known Issues

### Current Version (v0.5.1.1)
- **Security**: Multiple CVEs in DirectX SDK 2010
- **Security**: Outdated FBX SDK with known vulnerabilities  
- **Build**: Hard-coded paths in .props files
- **Compatibility**: May not work on Windows 11 without modifications
- **Performance**: Inefficient memory management patterns

### Workarounds
- **Build Issues**: Update paths in dxsdk.props and fbxsdk.props
- **Windows 11**: Run in compatibility mode if needed
- **Security**: Only process trusted .tri files from known sources

## Development Notes

### Code Quality Metrics
- **Lines of Code**: ~2,917 in main application
- **Dependencies**: 7 major libraries + Windows APIs
- **Test Coverage**: Currently 0% (tests planned)
- **Documentation**: Previously minimal, now comprehensive

### Performance Benchmarks
- **File Loading**: Varies by .tri file size and complexity
- **Rendering**: Depends on vertex count and texture resolution  
- **Memory Usage**: Not optimized, can be high for large models
- **Export Speed**: Limited by FBX SDK performance

## Roadmap

### Short Term (1-3 months)
- [ ] CMake build system
- [ ] Windows SDK migration  
- [ ] FBX SDK update
- [ ] Basic CI/CD pipeline

### Medium Term (3-6 months)
- [ ] C++17/20 upgrade
- [ ] Unit testing framework
- [ ] Memory usage optimization
- [ ] Cross-platform investigation

### Long Term (6+ months)
- [ ] Plugin architecture
- [ ] Additional file format support
- [ ] Performance improvements
- [ ] Modern UI framework evaluation

## Support

### Getting Help
- **Documentation**: Check README.md and guides first
- **Issues**: Search existing GitHub issues
- **Community**: Use GitHub Discussions for questions
- **Security**: Email maintainers directly for vulnerabilities

### Version Support
- **Current**: v0.5.1.1 (maintenance mode)
- **Next**: Focus on modernization and security
- **Legacy**: Limited support for older versions

### EOL Policy
- **DirectX SDK 2010**: Will be removed in next major version
- **FBX SDK 2013.3**: Will be updated to latest stable
- **Visual Studio 2010**: Support ending, migrate to VS 2019/2022
- **Windows 7/8.1**: Support may be dropped in future versions

---

**Semantic Versioning Note**: This project will adopt strict semantic versioning starting with the next release. Breaking changes will increment the major version number.

*For detailed technical changes, see commit history and pull requests on GitHub.*