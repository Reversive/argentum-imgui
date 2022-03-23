#pragma once

namespace argentum {
	class c_menu {
	private:
		struct {
			bool m_hidden{};
		} m_main{};
	public:
		void render();
	};

	inline const auto g_menu = std::make_unique< c_menu >();
}