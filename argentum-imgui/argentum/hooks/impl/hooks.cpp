#include "../../argentum.hpp"

namespace argentum::hooks {
	void __stdcall key_up(int p_this, __int16* key, int a3) {
		OutputDebugString("I am in key_up!");
		o_key_up(p_this, key, a3);
	}

	long D3DAPI dx9_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_params) {
		OutputDebugString("I am in reset!");
		const auto ret = o_dx9_reset(device, present_params);
		return ret;
	}

	long D3DAPI dx9_present(IDirect3DDevice9* device,
		RECT* src_rect, RECT* dst_rect, HWND dst_wnd_override, RGNDATA* dirty_region
	) {
		return o_dx9_present(device, src_rect, dst_rect, dst_wnd_override, dirty_region);
	}
}