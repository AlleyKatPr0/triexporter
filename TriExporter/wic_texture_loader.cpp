#include "wic_texture_loader.h"

#include <windows.h>
#include <wincodec.h>    // WIC
#include <vector>
#include <algorithm>
#include <cstring>

namespace {
struct ScopedCOM {
    bool needUninit = false;
    ScopedCOM() {
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        if (SUCCEEDED(hr)) needUninit = true;
        // If RPC_E_CHANGED_MODE, COM was already initialized in different mode; proceed without uninit.
    }
    ~ScopedCOM() {
        if (needUninit) CoUninitialize();
    }
};
} // namespace

static bool CopyFrameToTexture(IDirect3DDevice9* device,
                               IWICBitmapSource* src,
                               IDirect3DTexture9** outTexture) {
    UINT w = 0, h = 0;
    {
        UINT width = 0, height = 0;
        if (FAILED(src->GetSize(&width, &height))) return false;
        w = width; h = height;
    }

    // Create target texture (ARGB 8:8:8:8)
    IDirect3DTexture9* tex = nullptr;
    if (FAILED(device->CreateTexture(w, h, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, nullptr))) {
        return false;
    }

    D3DLOCKED_RECT lr{};
    if (FAILED(tex->LockRect(0, &lr, nullptr, 0))) {
        tex->Release();
        return false;
    }

    const UINT stride = w * 4;
    std::vector<BYTE> row(stride);

    // CopyPixels reads a full frame if rectangle is null; we read line by line.
    for (UINT y = 0; y < h; ++y) {
        if (FAILED(src->CopyPixels(nullptr, stride, stride, row.data()))) {
            tex->UnlockRect(0);
            tex->Release();
            return false;
        }
        std::memcpy(static_cast<BYTE*>(lr.pBits) + y * lr.Pitch, row.data(), stride);
    }

    tex->UnlockRect(0);
    *outTexture = tex; // pass ownership
    return true;
}

bool LoadTextureFromMemoryWIC(IDirect3DDevice9* device,
                              const void* data,
                              size_t size,
                              IDirect3DTexture9** outTexture) {
    if (!device || !data || size == 0 || !outTexture) return false;
    *outTexture = nullptr;

    ScopedCOM com;

    IWICImagingFactory* factory = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(&factory));
    if (FAILED(hr)) return false;

    IWICStream* stream = nullptr;
    hr = factory->CreateStream(&stream);
    if (SUCCEEDED(hr)) {
        hr = stream->InitializeFromMemory(reinterpret_cast<BYTE*>(const_cast<void*>(data)),
                                          static_cast<DWORD>(size));
    }
    if (FAILED(hr)) {
        if (stream) stream->Release();
        factory->Release();
        return false;
    }

    IWICBitmapDecoder* decoder = nullptr;
    hr = factory->CreateDecoderFromStream(stream, nullptr, WICDecodeMetadataCacheOnDemand, &decoder);
    if (FAILED(hr)) {
        stream->Release();
        factory->Release();
        return false;
    }

    IWICBitmapFrameDecode* frame = nullptr;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        decoder->Release();
        stream->Release();
        factory->Release();
        return false;
    }

    // Convert to 32bpp BGRA
    IWICFormatConverter* conv = nullptr;
    hr = factory->CreateFormatConverter(&conv);
    if (SUCCEEDED(hr)) {
        hr = conv->Initialize(frame, GUID_WICPixelFormat32bppBGRA,
                              WICBitmapDitherTypeNone, nullptr, 0.0f,
                              WICBitmapPaletteTypeCustom);
    }
    if (FAILED(hr)) {
        if (conv) conv->Release();
        frame->Release();
        decoder->Release();
        stream->Release();
        factory->Release();
        return false;
    }

    bool ok = CopyFrameToTexture(device, conv, outTexture);

    conv->Release();
    frame->Release();
    decoder->Release();
    stream->Release();
    factory->Release();

    return ok;
}