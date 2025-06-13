

#pragma once

#include <GLFW/glfw3.h>
#include "Audio_Manager.h"
#include "Game_Session.h"
#include "context.h"

class Input_Manager {
public:
    Input_Manager(context* ctx);

    void Update();           // polls events
    void Handle_Inputs();    // handles actual logic

    bool Is_Key_Pressed(int key) const;



private:
    context* ctx;
    bool left_mouse_pressed = false; // Track left mouse button state
};
