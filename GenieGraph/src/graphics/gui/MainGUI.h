#pragma once
#include "../../vendor/imgui/imgui.h"
#include "imgui_memory_editor.h"
#include "../../util/Basic.h"

struct MainGUI{

    // Settings
    bool Open;
    RuntimeVars* settings;

    MemoryEditor mem_editor;
    size_t mem_size = 256;
    void* mem_data_c0;
    void* mem_data_c1;
    void* mem_data_c2;
    void* mem_data_c3;
    void* mem_data_c4;
    void* mem_data_c5;
    void* mem_data_c6;
    void* mem_data_c7;

    MainGUI(RuntimeVars* s)
    {
        // Settings
        Open = true;
        settings = s;
        
    }

    void LoadGeneData(Colony * c) {
        mem_data_c0 = &c->gene_buffer[0];
        mem_data_c1 = &c->gene_buffer[256 * 1];
        mem_data_c2 = &c->gene_buffer[256 * 2];
        mem_data_c3 = &c->gene_buffer[256 * 3];
        mem_data_c4 = &c->gene_buffer[256 * 4];
        mem_data_c5 = &c->gene_buffer[256 * 5];
        mem_data_c6 = &c->gene_buffer[256 * 6];
        mem_data_c7 = &c->gene_buffer[256 * 7];
    }

    // Standalone Memory Editor window
    void DrawWindow(RuntimeVars* settings){
        
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, 0.0f), ImVec2(500, FLT_MAX));

        Open = true;
        if (ImGui::Begin("Controls", &Open)){
            if (ImGui::CollapsingHeader("Colony Controls")) {

                if (ImGui::Button("Start"))
                    settings->active = true;
                ImGui::SameLine();
                if (ImGui::Button("Stop"))
                    settings->active = false;
                ImGui::SameLine();
                if (ImGui::Button("Restart"))
                    settings->restart = true;

                ImGui::AlignTextToFramePadding();
                ImGui::Text("Simulation Speed:");
                ImGui::SameLine();

                // Arrow buttons with Repeater
                float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
                ImGui::PushButtonRepeat(true);
                if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (settings->speed > 1) settings->speed--; }
                ImGui::SameLine(0.0f, spacing);
                if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { settings->speed++; }
                ImGui::PopButtonRepeat();
                ImGui::SameLine();
                ImGui::Text("%d", settings->speed);

                ImGui::Text("Focused Colony:");
                ImGui::SameLine();
                // Arrow buttons with Repeater
                if (ImGui::ArrowButton("##left2", ImGuiDir_Left)) { if (settings->focused_colony > 0) settings->focused_colony--; }
                ImGui::SameLine(0.0f, spacing);
                if (ImGui::ArrowButton("##right2", ImGuiDir_Right)) { settings->focused_colony++; }
                ImGui::PopButtonRepeat();
                ImGui::SameLine();
                ImGui::Text("%d", settings->focused_colony);
            }
            if (ImGui::CollapsingHeader("Gene Editor")){
                if (ImGui::TreeNode("Chrome 0")) {
                    mem_editor.DrawContents(mem_data_c0, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 1")) {
                    mem_editor.HighlightMin -= 256;
                    mem_editor.HighlightMax -= 256;
                    mem_editor.DrawContents(mem_data_c1, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 2")) {
                    mem_editor.DrawContents(mem_data_c2, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 3")) {
                    mem_editor.DrawContents(mem_data_c3, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 4")) {
                    mem_editor.DrawContents(mem_data_c4, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 5")) {
                    mem_editor.DrawContents(mem_data_c5, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 6")) {
                    mem_editor.DrawContents(mem_data_c6, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 7")) {
                    mem_editor.DrawContents(mem_data_c7, mem_size, 0x0000);
                }
                
            }
            if (ImGui::CollapsingHeader("Camera Controls")) {

                ImGui::Checkbox("auto rotate", &settings->auto_rotate);

                ImGui::Spacing();
                ImGui::SliderAngle("x rotation", &settings->Rotate.x);
                ImGui::SliderAngle("y rotaton", &settings->Rotate.y);
                ImGui::SliderAngle("z rotation", &settings->Rotate.z);

                ImGui::Spacing();
                ImGui::DragFloat("x translation", &settings->Translate.x, 0.01f);
                ImGui::DragFloat("y translation", &settings->Translate.y, 0.01f);
                ImGui::DragFloat("z translation", &settings->Translate.z, 0.01f);
            }
        }
        ImGui::End();


    }

    void DrawMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void DrawOverlay(){
        const float PAD = 10.0f;
        bool p_open = true;
        static int corner = 0;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        
        if (corner != -1){
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }

        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

        if (ImGui::Begin("Main Dashboard", &p_open, window_flags)){
            ImGui::Text("Main Dash\n" "in the corner of the screen.\n" "(right-click to change position)");
            ImGui::Separator();
            ImGui::Text("FPS: (%.1i)", settings->fps);
           
            if (ImGui::BeginPopupContextWindow()){
                if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
                if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
                if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
                if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
                if (&p_open && ImGui::MenuItem("Close")) p_open = false;
                ImGui::EndPopup();
            }

            if (ImGui::CollapsingHeader("Colony Controls")) {

                if (ImGui::Button("Start"))
                    settings->active = true;
                ImGui::SameLine();
                if (ImGui::Button("Stop"))
                    settings->active = false;
                ImGui::SameLine();
                if (ImGui::Button("Restart"))
                    settings->restart = true;

                ImGui::AlignTextToFramePadding();
                ImGui::Text("Simulation Speed:");
                ImGui::SameLine();

                // Arrow buttons with Repeater
                float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
                ImGui::PushButtonRepeat(true);
                if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (settings->speed > 1) settings->speed--; }
                ImGui::SameLine(0.0f, spacing);
                if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { settings->speed++; }
                ImGui::PopButtonRepeat();
                ImGui::SameLine();
                ImGui::Text("%d", settings->speed);

                ImGui::Text("Focused Colony:");
                ImGui::SameLine();
                // Arrow buttons with Repeater
                ImGui::PushButtonRepeat(true);

                if (ImGui::ArrowButton("##left2", ImGuiDir_Left)) { if (settings->focused_colony > 0) settings->focused_colony--; }
                ImGui::SameLine(0.0f, spacing);
                if (ImGui::ArrowButton("##right2", ImGuiDir_Right)) { settings->focused_colony++; }
                ImGui::PopButtonRepeat();
                ImGui::SameLine();
                ImGui::Text("%d", settings->focused_colony);
            }
            if (ImGui::CollapsingHeader("Gene Editor")) {
                if (ImGui::TreeNode("Chrome 0")) {
                    mem_editor.DrawContents(mem_data_c0, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 1")) {
                    mem_editor.HighlightMin -= 256;
                    mem_editor.HighlightMax -= 256;
                    mem_editor.DrawContents(mem_data_c1, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 2")) {
                    mem_editor.DrawContents(mem_data_c2, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 3")) {
                    mem_editor.DrawContents(mem_data_c3, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 4")) {
                    mem_editor.DrawContents(mem_data_c4, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 5")) {
                    mem_editor.DrawContents(mem_data_c5, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 6")) {
                    mem_editor.DrawContents(mem_data_c6, mem_size, 0x0000);
                }
                if (ImGui::TreeNode("Chrome 7")) {
                    mem_editor.DrawContents(mem_data_c7, mem_size, 0x0000);
                }

            }
            if (ImGui::CollapsingHeader("Camera Controls")) {

                ImGui::Checkbox("auto rotate", &settings->auto_rotate);

                ImGui::Spacing();
                ImGui::SliderAngle("x rotation", &settings->Rotate.x);
                ImGui::SliderAngle("y rotaton", &settings->Rotate.y);
                ImGui::SliderAngle("z rotation", &settings->Rotate.z);

                ImGui::Spacing();
                ImGui::DragFloat("x translation", &settings->Translate.x, 0.01f);
                ImGui::DragFloat("y translation", &settings->Translate.y, 0.01f);
                ImGui::DragFloat("z translation", &settings->Translate.z, 0.01f);
            }

        }



        ImGui::End();
    }

    void updateHighlight(int chrome, int pos) {
        mem_editor.HighlightMin = (256*chrome) + pos;
        mem_editor.HighlightMax = (256 * chrome) + pos+ 2;
    }
    
};
