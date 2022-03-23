#include "../../argentum.hpp"

namespace argentum {
	void c_menu::render() {
		if (m_main.m_hidden) {
			return;
		}
		ImGui::Begin("Argentum Online by Reversive");
		// Draw whatever you want here for your ao menu

		ImGui::End();
	}
}