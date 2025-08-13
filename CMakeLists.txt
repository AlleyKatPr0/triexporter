cmake_minimum_required(VERSION 3.24)
project(TriExporter LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4 /permissive- /utf-8)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(WIN32)
  add_definitions(-DUNICODE -D_UNICODE)
endif()

# Dependencies via vcpkg
find_package(assimp CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

if(WIN32)
  set(WIC_LIBS windowscodecs ole32)
endif()

# Placeholder source discovery (will be populated after migration)
file(GLOB_RECURSE APP_SOURCES
  CONFIGURE_DEPENDS
  src/*.cpp
  src/*.c
)

if(NOT APP_SOURCES)
  message(STATUS "No sources found under src/. This is a scaffold and won't build until sources are migrated.")
  add_custom_target(TriExporter ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Modernization scaffold present. Migrate sources to CMake to enable build."
  )
else()
  add_executable(TriExporter ${APP_SOURCES})
  target_include_directories(TriExporter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_link_libraries(TriExporter PRIVATE
    assimp::assimp
    PNG::PNG
    ZLIB::ZLIB
    spdlog::spdlog
    fmt::fmt
  )
  if(WIN32)
    target_link_libraries(TriExporter PRIVATE ${WIC_LIBS})
    target_compile_definitions(TriExporter PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
  endif()
  if(MSVC)
    target_compile_definitions(TriExporter PRIVATE
      _CRT_SECURE_NO_WARNINGS
      _SCL_SECURE_NO_WARNINGS
    )
  endif()
endif()