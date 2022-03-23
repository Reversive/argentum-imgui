#pragma once
namespace argentum {
	class c_engine {
	private:
		WNDCLASSEX m_wclass;
		HWND m_dummy_hwnd;
		HWND m_hwnd;
		uint32_t* m_vft;
		bool init_render_window() const;
		bool init_directx_window() const;
		void delete_window() const;
	public:
		bool init_directx() const;
		uint32_t* get_vft() const;
		HWND get_window() const;
		void set_window(HWND hwnd) const;
	};
	inline const auto g_engine = std::make_unique< c_engine >();
}