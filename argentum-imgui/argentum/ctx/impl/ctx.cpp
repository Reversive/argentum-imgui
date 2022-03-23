#include "../../argentum.hpp"

int __stdcall DllMain(_In_ HINSTANCE instance, _In_ DWORD reason, _In_ LPVOID reserved) {
	if (reason != DLL_PROCESS_ATTACH)
		return 0;

	DisableThreadLibraryCalls(instance);
	std::jthread{ []() {
		argentum::g_ctx->run();}
	}.detach();
	return 1;
}

namespace argentum {
	void c_ctx::run() {
		OutputDebugString("Wohoo this works!");
	}

	void c_ctx::init_imgui() const {
		// todo
	}
}