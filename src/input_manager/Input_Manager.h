

#pragma once

#include <GLFW/glfw3.h>
#include "Audio_Manager.h"
#include "Game_Session.h"

class Input_Manager {
public:
    Input_Manager(GLFWwindow* window, Audio_Manager* audio);

    void Update();           // polls events
    void Handle_Inputs();    // handles actual logic

    bool Is_Key_Pressed(int key) const;

    void set_game_session(Game_Session* session);

private:
    GLFWwindow* window;
    Audio_Manager* audio_system;
    Game_Session* game_session; 
    bool left_mouse_pressed = false; // Track left mouse button state
};
