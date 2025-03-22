#include "state.h"

#include "stdio.h"
#include "SDL3/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include "SDL3/SDL_opengles2.h"
#else
#include "SDL3/SDL_opengl.h"
#endif

bool GizmoState::init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    SDL_Window* window = SDL_CreateWindow("Gizmo", 640, 576, window_flags);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        printf("SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_GL_MakeCurrent(window, gl_context)) {
        printf("SDL_GL_MakeCurrent Error: %s\n", SDL_GetError());
        return false;
    }
    
    SDL_GL_SetSwapInterval(1); // Enable vsync
    SDL_ShowWindow(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewports
    // io.ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;      // Disable docking

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void GizmoState::shutdown() {
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_GLContext gl_context = SDL_GL_GetCurrentContext();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    if (gl_context)
        SDL_GL_DestroyContext(gl_context);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void GizmoState::handle_events(SDL_Window* window, SDL_Event& event, bool& should_quit) {
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
            should_quit = true;
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
            should_quit = true;
    }
}

void GizmoState::draw(SDL_Window* window) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
        ImGui::Text("Gizmo");
        ImGui::Separator();
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    {
        static int counter = 0;
        ImGui::Begin("Hello, World!");
        ImGui::Text("This is an example window.");
        if (ImGui::Button("Click me"))
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, 1280, 720);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    SDL_GL_SwapWindow(window);
}
