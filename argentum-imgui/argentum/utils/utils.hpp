#pragma once

namespace argentum {
	MODULEINFO get_module_info(char* sz_module);
	uint32_t find_pattern(const char* pattern, const char* mask, const char* module = NULL);
}