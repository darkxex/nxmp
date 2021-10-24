#include "gui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "windows.h"
#include "utils.h"
#include "localfiles.h"
#include "Enigma2.h"


namespace Windows {
    void EnigmaWindow(bool *focus, bool *first_item) {
        Windows::SetupWindow();
		static unsigned int item_current_idx = 0;
        std::vector<std::string> topmenu = {"Local Files","Network","Enigma2"};
		
        if (ImGui::Begin("Enigma2", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar)) {
			ImGui::SetNextWindowFocus();
            if (ImGui::BeginListBox("Enigma2 Browser Menu",ImVec2(1280.0f, 720.0f))){
				if(item.enigma2bouquet == ""){
					for (unsigned int n = 0; n < enigma2->e2services.size(); n++){
						static int selected = -1;
						if (ImGui::Selectable(enigma2->e2services[n].name.c_str(), selected == n)){
			
							enigma2->m3uParser((char *)enigma2->e2services[n].bouquetref.c_str());
							item.enigma2bouquet =  enigma2->e2services[n].bouquetref;
						}
						if (selected)
							ImGui::SetItemDefaultFocus();
							
					}
					if (*first_item) {
						ImGui::SetFocusID(ImGui::GetID(enigma2->e2services[0].name.c_str()), ImGui::GetCurrentWindow());
						*first_item = false;
					}
				}else if(item.enigma2bouquet != ""){
					for (unsigned int n = 0; n < enigma2->e2currbouqet.size(); n++){
						static int selected = -1;
						std::string channame = std::to_string(n) + std::string(". ") +enigma2->e2currbouqet[n].name;
						if (ImGui::Selectable(channame.c_str(), selected == n)){
									
							const char *cmd[] = {"loadfile", enigma2->e2currbouqet[n].url.c_str(), NULL};
							mpv_command_async(mpv->getHandle(), 0, cmd);
						}
						if (selected)
						ImGui::SetItemDefaultFocus();
					}
					if (*first_item) {
						std::string channame = std::to_string(0) + std::string(". ") +enigma2->e2currbouqet[0].name;
						ImGui::SetFocusID(ImGui::GetID(channame.c_str()), ImGui::GetCurrentWindow());
						*first_item = false;
					}
				}
			}
			ImGui::EndListBox();
		}
		Windows::ExitWindow();
	}
}