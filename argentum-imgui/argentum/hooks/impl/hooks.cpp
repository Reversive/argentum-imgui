#include "../../argentum.hpp"

namespace argentum::hooks {
	void __stdcall key_up(int p_this, __int16* key, int a3) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(*(__int16*)key);
		o_key_up(p_this, key, a3);
	}

	long D3DAPI dx9_reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_params) {
		
		ImGui_ImplDX9_InvalidateDeviceObjects();

		const auto ret = o_dx9_reset(device, present_params);

		ImGui_ImplDX9_CreateDeviceObjects();

		return ret;
	}

	bool initialised = false;

	long D3DAPI dx9_present(IDirect3DDevice9* device,
		RECT* src_rect, RECT* dst_rect, HWND dst_wnd_override, RGNDATA* dirty_region
	) {
		if (GetForegroundWindow() != g_engine->get_window())
		{
			g_engine->set_window(GetForegroundWindow());
			initialised = !initialised;
		}
		if(!dst_wnd_override) {
			if (!initialised) {
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
				ImGui_ImplWin32_Init(g_engine->get_window());
				ImGui_ImplDX9_Init(device);
				ImGui_ImplDX9_CreateDeviceObjects();
				ImGui::GetIO().ImeWindowHandle = g_engine->get_window();
				initialised = true;
			}
			ImGui_ImplDX9_NewFrame();
			ImGuiIO& io = ImGui::GetIO();
			POINT p = {};
			GetCursorPos(&p);
			ImGui_ImplWin32_NewFrame();
			ScreenToClient(g_engine->get_window(), &p);
			io.MousePos.x = p.x - 7;
			io.MousePos.y = p.y - 150;
			ImGui::NewFrame();
			for (int i = 6; i < 256; i++) {
				io.KeysDown[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
			}

			io.MouseDown[0] = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
			io.MouseDown[1] = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
			ImGui::ShowDemoWindow();
			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}
		return o_dx9_present(device, src_rect, dst_rect, dst_wnd_override, dirty_region);
	}
}