#pragma once
#include <d3d9.h>
#include <cstddef>

// Loads a texture from an image encoded in memory (PNG/JPG/BMP/TIFF/etc) using WIC.
// Returns true on success and writes an AddRef'ed texture to *outTexture.
// The caller must Release() the returned texture.
bool LoadTextureFromMemoryWIC(IDirect3DDevice9* device,
                              const void* data,
                              size_t size,
                              IDirect3DTexture9** outTexture);