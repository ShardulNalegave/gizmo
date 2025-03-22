#include "stdio.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "SDL3/SDL.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif

#include "state.h"

int main() {
    if (!GizmoState::init()) {
        printf("State initialization failed!\n");
        return -1;
    }

    SDL_Window* window = SDL_GL_GetCurrentWindow();
    bool should_quit = false;
    SDL_Event event;

    while (!should_quit) {
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        GizmoState::handle_events(window, event, should_quit);
        GizmoState::draw(window);
    }

    GizmoState::shutdown();
    return 0;
}
