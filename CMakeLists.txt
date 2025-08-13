cmake_minimum_required(VERSION 3.20)
project(TriExporter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find vcpkg packages
find_package(PkgConfig REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Set up source directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# This is a skeleton CMakeLists.txt that will be used once sources are migrated to src/
# For now, create an empty target to allow configuration to succeed
add_custom_target(triexporter-cmake-skeleton
    COMMENT "CMake skeleton - sources will be migrated to src/ in future PRs"
)

# Installation placeholder
install(FILES README.md DESTINATION .)