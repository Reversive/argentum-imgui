#pragma once

namespace argentum::hooks {
    void __stdcall key_up(int p_this, __int16* key, int a3);
    inline decltype(&key_up) o_key_up{};

    long D3DAPI dx9_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_params);
    inline decltype(&dx9_reset) o_dx9_reset{};

    long D3DAPI dx9_present(IDirect3DDevice9* device,
        RECT* src_rect, RECT* dst_rect, HWND dst_wnd_override, RGNDATA* dirty_region
    );
    inline decltype(&dx9_present) o_dx9_present{};
}