#pragma once

#include <d3d9.h>
#include <minhook/minhook.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>


#if defined( _WIN32 ) || defined( _WIN64 )
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define D3D9_VMT_SIZE 119
#define RESET_INDEX 16u
#define PRESENT_INDEX 17u
#include <windows.h>
#endif

#include <memory>
#include <thread>
#include <Psapi.h>
#include "ctx/ctx.hpp"
#include "hooks/hooks.hpp"
#include "engine/engine.hpp"
#include "menu/menu.hpp"
#include "utils/utils.hpp"