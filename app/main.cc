
#include "app.h"

int main() {
    GizmoApp app;
    if (app.init() != 0) return -1;

    app.run();
    
    return 0;
}
