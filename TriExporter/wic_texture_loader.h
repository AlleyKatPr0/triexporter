#pragma once

#include <d3d9.h>

/**
 * @brief Load a texture from memory using Windows Imaging Component (WIC)
 * 
 * This function uses WIC to decode image data from memory and create a Direct3D9 texture.
 * The texture is created in A8R8G8B8 format with 32-bit BGRA pixels.
 * 
 * @param device Pointer to the Direct3D9 device
 * @param data Pointer to the image data in memory
 * @param size Size of the image data in bytes
 * @param outTexture Pointer to receive the created texture (output parameter)
 * @return true if the texture was loaded successfully, false otherwise
 */
bool LoadTextureFromMemoryWIC(IDirect3DDevice9* device, const void* data, size_t size, IDirect3DTexture9** outTexture);