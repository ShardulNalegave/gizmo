#ifndef GIZMO_STATE_H
#define GIZMO_STATE_H

#include <SDL3/SDL.h>

namespace GizmoState {
    bool init();
    void shutdown();
    void handle_events(SDL_Window*, SDL_Event&, bool&);
    void draw(SDL_Window*);
}

#endif // GIZMO_STATE_H
