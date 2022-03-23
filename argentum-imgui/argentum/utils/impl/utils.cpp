#include "../../argentum.hpp"

#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define GETBITS( x )	(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE( x )	(GETBITS(x[0]) << 4 | GETBITS(x[1]))

namespace argentum {

	MODULEINFO get_module_info(const char* sz_module) {
		MODULEINFO mod_info = { 0 };
		HMODULE h_module = GetModuleHandle(sz_module);
		if (h_module == 0)
			return mod_info;
		GetModuleInformation(GetCurrentProcess(), h_module, &mod_info, sizeof(MODULEINFO));
		return mod_info;
	}

	uint32_t find_pattern(const char* pattern, const char* mask, const char* module) {
		MODULEINFO m_info = get_module_info(module);
		DWORD base = (DWORD)m_info.lpBaseOfDll;
		DWORD size = (DWORD)m_info.SizeOfImage;
		DWORD pattern_length = (DWORD)strlen(mask);

		for (DWORD i = 0; i < size - pattern_length; i++) {
			bool found = true;

			for (DWORD j = 0; j < pattern_length; j++) {
				found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
			}

			if (found) {
				return base + i;
			}
		}

		return NULL;
	}
}
