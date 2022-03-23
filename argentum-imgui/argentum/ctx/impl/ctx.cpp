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
		// todo: pattern scan this function
		HOOK(0x597510, hooks::key_up, hooks::o_key_up);
	}

	void c_ctx::init_imgui() const {
		// todo
	}

}

#undef HOOK_VFUNC
#undef THROW