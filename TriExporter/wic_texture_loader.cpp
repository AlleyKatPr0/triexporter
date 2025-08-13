#include "stdafx.h"
#include "wic_texture_loader.h"

#include <wincodec.h>
#include <comdef.h>
#include <memory>

bool LoadTextureFromMemoryWIC(IDirect3DDevice9* device, const void* data, size_t size, IDirect3DTexture9** outTexture)
{
    if (!device || !data || size == 0 || !outTexture)
    {
        return false;
    }

    *outTexture = nullptr;

    HRESULT hr = S_OK;

    // Initialize COM if not already initialized
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    // Create WIC factory
    IWICImagingFactory* wicFactory = nullptr;
    hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicFactory);
    if (FAILED(hr))
    {
        return false;
    }

    // Create WIC stream
    IWICStream* stream = nullptr;
    hr = wicFactory->CreateStream(&stream);
    if (FAILED(hr))
    {
        wicFactory->Release();
        return false;
    }

    // Initialize stream with memory data
    hr = stream->InitializeFromMemory(const_cast<BYTE*>(static_cast<const BYTE*>(data)), static_cast<DWORD>(size));
    if (FAILED(hr))
    {
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Create decoder
    IWICBitmapDecoder* decoder = nullptr;
    hr = wicFactory->CreateDecoderFromStream(stream, nullptr, WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr))
    {
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Get first frame
    IWICBitmapFrameDecode* frame = nullptr;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr))
    {
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Create format converter to ensure we get 32bpp BGRA
    IWICFormatConverter* converter = nullptr;
    hr = wicFactory->CreateFormatConverter(&converter);
    if (FAILED(hr))
    {
        frame->Release();
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Initialize the format converter to 32bpp BGRA
    hr = converter->Initialize(frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeMedianCut);
    if (FAILED(hr))
    {
        converter->Release();
        frame->Release();
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Get image dimensions
    UINT width, height;
    hr = converter->GetSize(&width, &height);
    if (FAILED(hr))
    {
        converter->Release();
        frame->Release();
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Create D3D texture
    IDirect3DTexture9* texture = nullptr;
    hr = device->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, nullptr);
    if (FAILED(hr))
    {
        converter->Release();
        frame->Release();
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Lock texture for writing
    D3DLOCKED_RECT lockedRect;
    hr = texture->LockRect(0, &lockedRect, nullptr, 0);
    if (FAILED(hr))
    {
        texture->Release();
        converter->Release();
        frame->Release();
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Calculate stride and allocate temporary buffer
    const UINT stride = width * 4; // 4 bytes per pixel (32bpp BGRA)
    const UINT imageSize = stride * height;
    std::unique_ptr<BYTE[]> imageData(new BYTE[imageSize]);

    // Copy pixel data from WIC converter
    hr = converter->CopyPixels(nullptr, stride, imageSize, imageData.get());
    if (FAILED(hr))
    {
        texture->UnlockRect(0);
        texture->Release();
        converter->Release();
        frame->Release();
        decoder->Release();
        stream->Release();
        wicFactory->Release();
        return false;
    }

    // Copy rows to D3D texture, handling potential pitch differences
    BYTE* srcRow = imageData.get();
    BYTE* destRow = static_cast<BYTE*>(lockedRect.pBits);
    
    for (UINT row = 0; row < height; ++row)
    {
        memcpy(destRow, srcRow, stride);
        srcRow += stride;
        destRow += lockedRect.Pitch;
    }

    // Unlock texture
    texture->UnlockRect(0);

    // Clean up WIC resources
    converter->Release();
    frame->Release();
    decoder->Release();
    stream->Release();
    wicFactory->Release();

    // Return the created texture
    *outTexture = texture;
    return true;
}