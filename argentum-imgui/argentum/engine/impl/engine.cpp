#include "../../argentum.hpp"

namespace argentum {
	uint32_t* c_engine::get_vft() const {
		return g_engine->m_vft;
	}
	bool c_engine::init_directx() const {
		if (!init_window()) {
			return false;
		}

		LPDIRECT3D9 direct3d9 = Direct3DCreate9(D3D_SDK_VERSION);
		if (direct3d9 == nullptr) {
			delete_window();
			return false;
		}

		D3DDISPLAYMODE display_mode;
		if (direct3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode) < 0) {
			delete_window();
			return false;
		}

		D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = display_mode.Format;
		params.BackBufferCount = 0;
		params.MultiSampleType = D3DMULTISAMPLE_NONE;
		params.MultiSampleQuality = NULL;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.hDeviceWindow = g_engine->m_hwnd;
		params.Windowed = true;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
		params.Flags = NULL;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = 0;

		LPDIRECT3DDEVICE9 device;
		if (direct3d9->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, g_engine->m_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
			&params, &device) < 0
			) {
			direct3d9->Release();
			delete_window();
			return false;
		}

		g_engine->m_vft = (uint32_t*)::calloc(D3D9_VMT_SIZE, sizeof(uint32_t));
		if (g_engine->m_vft == nullptr) {
			return false;
		}
		memcpy(g_engine->m_vft, *(uint32_t**)device, 119 * sizeof(uint32_t));
		direct3d9->Release();
		direct3d9 = NULL;
		device->Release();
		device = NULL;
		delete_window();
		return true;
	}

	bool c_engine::init_window() const {
		g_engine->m_wclass.cbSize = sizeof(WNDCLASSEX);
		g_engine->m_wclass.style = CS_HREDRAW | CS_VREDRAW;
		g_engine->m_wclass.lpfnWndProc = DefWindowProc;
		g_engine->m_wclass.cbClsExtra = 0;
		g_engine->m_wclass.cbWndExtra = 0;
		g_engine->m_wclass.hInstance = GetModuleHandle(NULL);
		g_engine->m_wclass.hIcon = NULL;
		g_engine->m_wclass.hCursor = NULL;
		g_engine->m_wclass.hbrBackground = NULL;
		g_engine->m_wclass.lpszMenuName = NULL;
		g_engine->m_wclass.lpszClassName = "MJ";
		g_engine->m_wclass.hIconSm = NULL;
		RegisterClassEx(&g_engine->m_wclass);
		g_engine->m_hwnd = CreateWindow(g_engine->m_wclass.lpszClassName, "DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, g_engine->m_wclass.hInstance, NULL);
		if (g_engine->m_hwnd == NULL) {
			return false;
		}
		return true;
	}

	void c_engine::delete_window() const {
		DestroyWindow(g_engine->m_hwnd);
		UnregisterClass(g_engine->m_wclass.lpszClassName, g_engine->m_wclass.hInstance);
	}
}
