#include "../../argentum.hpp"

int __stdcall DllMain(_In_ HINSTANCE instance, _In_ DWORD reason, _In_ LPVOID reserved) {
	if (reason != DLL_PROCESS_ATTACH)
		return 0;

	DisableThreadLibraryCalls(instance);
	std::jthread{ []() {
		argentum::g_ctx->run(); }
	}.detach();
	return 1;
}

#ifdef _DEBUG
#define THROW( exception ) throw std::runtime_error{ exception };
#else
#define THROW( exception ) return
#endif

#define HOOK( target, hook, original ) \
    if ( MH_CreateHook( reinterpret_cast<LPVOID>(target), \
        reinterpret_cast< LPVOID >( &hook ), reinterpret_cast< LPVOID* >( &original ) ) != MH_OK ) \
        THROW( "can't hook " #hook "." ) \

#define HOOK_VFUNC( vft, index, hook, original ) \
    if ( MH_CreateHook(  reinterpret_cast<LPVOID>(vft[index]), \
        reinterpret_cast< LPVOID >( &hook ), reinterpret_cast< LPVOID* >( &original ) ) != MH_OK ) \
        THROW( "Can't hook " #hook "." ) \

namespace argentum {
	void c_ctx::run() {
		if (!g_engine->init_directx()) {
			THROW("Can't initialize DirectX device");
			return;
		}
		
		if (MH_Initialize() != MH_OK) {
			THROW("Can't initialize MinHook");
		}

		init_hooks();

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			THROW("There was a problem enabling some hook.");
	}

	void c_ctx::init_hooks() const {
		HOOK_VFUNC(g_engine->get_vft(), PRESENT_INDEX, hooks::dx9_present, hooks::o_dx9_present);
		HOOK_VFUNC(g_engine->get_vft(), RESET_INDEX, hooks::dx9_reset, hooks::o_dx9_reset);
		uint32_t scan_result = find_pattern("\x8D\x45\xA0\x50\x8B\x4D\x88\x8B\x11\x8B\x45\x88\x50\xFF\x92\x00\x00\x00\x00\xDB\xE2\x89\x45\x84\x83\x7D\x84\x00", "xxxxxxxxxxxxxxx????xxxxxxxxx");
		HOOK(scan_result - 0x8F, hooks::key_up, hooks::o_key_up);
	}

}

#undef HOOK_VFUNC
#undef THROW