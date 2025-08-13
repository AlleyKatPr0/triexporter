# Contributing to TriExporter

Thank you for your interest in contributing to TriExporter! This project is in need of modernization and we welcome all contributions, especially those focused on security and maintainability improvements.

## 🚨 Priority Areas

### Critical (Security Issues)
1. **Dependency Updates**: Replace outdated DirectX SDK 2010 and FBX SDK 2013.3
2. **Vulnerability Fixes**: Address known security issues in legacy libraries  
3. **Memory Safety**: Replace manual memory management with modern C++ practices
4. **Input Validation**: Add proper validation for file operations

### High Priority (Stability & Build)
1. **Build System**: Add CMake support alongside Visual Studio
2. **CI/CD Pipeline**: Implement automated builds and testing
3. **Cross-Platform**: Investigate Linux/macOS compatibility
4. **Documentation**: Improve code comments and API documentation

### Medium Priority (Code Quality)
1. **Modern C++**: Upgrade from C++98/03 to C++17/20
2. **Unit Tests**: Add comprehensive test coverage
3. **Code Style**: Standardize formatting and conventions
4. **Error Handling**: Implement consistent exception handling

## Getting Started

### Development Environment Setup

#### Requirements
- **OS**: Windows 10/11 (primary), Linux/macOS (future)
- **IDE**: Visual Studio 2019/2022 Community or higher
- **Tools**: Git, CMake 3.20+, vcpkg (recommended)
- **Hardware**: 8GB RAM, 50GB free space for SDKs

#### Quick Setup
```bash
# Clone the repository
git clone https://github.com/AlleyKatPr0/triexporter.git
cd triexporter

# Install vcpkg (recommended for dependency management)
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg integrate install

# Install dependencies
./vcpkg install libpng zlib
```

#### Legacy Setup (Current)
1. Install Visual Studio 2019/2022 with C++ desktop development
2. Download and install Windows SDK 10.0.22621.0+
3. Register and download FBX SDK from Autodesk
4. Update paths in `dxsdk.props` and `fbxsdk.props`
5. Open `TriExporter.sln` and build

### First Contribution Ideas

#### Easy (Good First Issues)
- [ ] Fix compiler warnings in Release build
- [ ] Update .gitignore for modern C++ development
- [ ] Add missing const correctness
- [ ] Replace NULL with nullptr
- [ ] Add basic input validation checks

#### Medium (Intermediate)
- [ ] Create CMakeLists.txt for main project
- [ ] Add unit tests for TriFile class
- [ ] Replace raw pointers with smart pointers
- [ ] Implement proper logging system
- [ ] Add command-line interface option

#### Hard (Advanced)
- [ ] Update FBX SDK to latest version
- [ ] Replace DirectX SDK with Windows SDK
- [ ] Add cross-platform file dialog support
- [ ] Implement plugin architecture for file formats
- [ ] Add memory usage optimization

## Contribution Guidelines

### Code Style

#### Naming Conventions
```cpp
// Classes: PascalCase
class TriFile {
public:
    // Methods: PascalCase (existing) or camelCase (new code)
    bool LoadFile(const std::string& filename);
    
    // Variables: camelCase preferred for new code
    int vertexCount;
    
    // Constants: ALL_CAPS with underscores
    static const int MAX_VERTICES = 65536;
    
    // Private members: prefix with m_
private:
    std::vector<Vertex> m_vertices;
};
```

#### Modern C++ Practices
```cpp
// Prefer smart pointers over raw pointers
std::unique_ptr<TriFile> file = std::make_unique<TriFile>();

// Use auto for complex types
auto result = someComplexFunction();

// Range-based loops when possible
for (const auto& vertex : vertices) {
    // Process vertex
}

// RAII for resource management
class TextureManager {
    std::unique_ptr<ID3D11Texture2D> m_texture;
public:
    TextureManager() = default;
    ~TextureManager() = default; // Automatic cleanup
};
```

#### File Organization
- **Headers (.h)**: Class declarations, inline functions
- **Source (.cpp)**: Implementation details
- **One class per file** when reasonable
- **Group related functionality** in namespaces

### Testing

#### Unit Tests (Future)
```cpp
// Use Google Test framework
TEST(TriFileTest, LoadValidFile) {
    TriFile file;
    EXPECT_TRUE(file.Load("test_data/valid.tri"));
    EXPECT_GT(file.GetVertexCount(), 0);
    EXPECT_LT(file.GetVertexCount(), 1000000); // Sanity check
}

TEST(TriFileTest, RejectInvalidFile) {
    TriFile file;
    EXPECT_FALSE(file.Load("test_data/invalid.tri"));
    EXPECT_EQ(file.GetVertexCount(), 0);
}
```

#### Integration Tests
- Test with actual EVE Online .tri files
- Verify FBX export compatibility
- Validate 3D rendering output
- Performance benchmarking

### Security Considerations

#### Input Validation
```cpp
bool TriFile::LoadFromFile(const std::string& filename) {
    // Always validate inputs
    if (filename.empty()) {
        LogError("Empty filename provided");
        return false;
    }
    
    // Check file size limits
    std::error_code ec;
    auto fileSize = std::filesystem::file_size(filename, ec);
    if (ec || fileSize > MAX_FILE_SIZE) {
        LogError("File too large or inaccessible: {}", filename);
        return false;
    }
    
    // Continue with validated input...
}
```

#### Memory Safety
```cpp
// Avoid buffer overruns
std::vector<char> ReadFileData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }
    
    // Get file size safely
    file.seekg(0, std::ios::end);
    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<char> buffer(size);
    file.read(buffer.data(), size);
    
    return buffer; // RAII cleanup
}
```

## Pull Request Process

### Before Submitting
1. **Fork the repository** and create a feature branch
2. **Test your changes** thoroughly
3. **Update documentation** if needed
4. **Add tests** for new functionality
5. **Follow code style** guidelines

### PR Guidelines
1. **Clear Title**: Describe what the PR accomplishes
2. **Detailed Description**: Explain the changes and reasoning
3. **Link Issues**: Reference related GitHub issues
4. **Test Results**: Include test output or screenshots
5. **Breaking Changes**: Clearly document any breaking changes

### PR Template
```markdown
## Summary
Brief description of changes

## Changes Made
- [ ] Updated dependency X to version Y
- [ ] Added unit tests for feature Z
- [ ] Fixed memory leak in component A

## Testing
- [ ] Unit tests pass
- [ ] Integration tests pass  
- [ ] Manual testing with sample files
- [ ] Performance impact assessed

## Screenshots (if applicable)
[Include screenshots for UI changes]

## Breaking Changes
[List any breaking changes and migration path]

## Checklist
- [ ] Code follows project style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] Tests added/updated
```

## Communication

### Getting Help
- **GitHub Discussions**: General questions and ideas
- **GitHub Issues**: Bug reports and feature requests
- **Pull Request Comments**: Code review discussions
- **Security Issues**: Email maintainers directly (see SECURITY.md)

### Code Review Process
1. **Automated Checks**: CI/CD pipeline must pass
2. **Maintainer Review**: At least one maintainer approval
3. **Security Review**: Security-related changes need extra review
4. **Testing**: Manual testing may be required for complex changes

### Response Times
- **Issues**: Response within 1-2 weeks
- **Pull Requests**: Initial review within 1 week
- **Security Issues**: Response within 48 hours

## Recognition

### Contributors
All contributors will be recognized in:
- **README.md**: Contributors section
- **CHANGELOG.md**: Release notes
- **GitHub**: Contributor statistics
- **Releases**: Special recognition for major contributions

### Types of Contributions
- **Code**: Bug fixes, features, optimizations
- **Documentation**: README, guides, code comments
- **Testing**: Test cases, bug reports, validation
- **Design**: UI/UX improvements, architecture
- **Security**: Vulnerability reports, security fixes
- **Infrastructure**: Build systems, CI/CD, automation

## License

By contributing to TriExporter, you agree that your contributions will be licensed under the same license as the project. Please ensure you have the right to contribute any code or content you submit.

## Resources

### Learning Resources
- [Modern C++ Guidelines](https://github.com/isocpp/CppCoreGuidelines)
- [Visual Studio Documentation](https://docs.microsoft.com/en-us/visualstudio/)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/)
- [Git Best Practices](https://git-scm.com/book/en/v2)

### Development Tools
- **IDEs**: Visual Studio, Visual Studio Code, CLion
- **Static Analysis**: PVS-Studio, Clang-Tidy, SonarQube
- **Debugging**: Visual Studio Debugger, GDB, Valgrind
- **Performance**: Intel VTune, Visual Studio Profiler

Thank you for contributing to TriExporter! Together we can modernize this project and make it a valuable tool for the EVE Online community.