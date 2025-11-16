
#ifndef GIZMO_APP_H
#define GIZMO_APP_H

#include <SDL3/SDL.h>
#include <imgui.h>

class GizmoApp {
public:
    GizmoApp();
    ~GizmoApp();

    int init();
    void run();

private:
    int init_sdl();
    int init_imgui();

    void imgui_shutdown();
    void sdl_shutdown();

    int render();

    SDL_GLContext glContext_;
    SDL_Window *window_;
    const char* glslVersion_;
    float mainScale_;

    ImGuiIO *imguiIO_;
};

#endif
