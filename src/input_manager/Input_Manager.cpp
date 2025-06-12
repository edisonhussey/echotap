// #include "Input_Manager.h"
// #include "Audio_Manager.h" // Now we can include it
// #include <GLFW/glfw3.h>

// GLFWwindow* Input_Manager::window = nullptr;
// Audio_Manager* Input_Manager::audioSystem = nullptr;

// void Input_Manager::Init(GLFWwindow* win) {
//     window = win;
// }

// void Input_Manager::SetAudio(Audio_Manager* audio) {
//     // audioSystem = audio;
// }

// void Input_Manager::Update() {
//     glfwPollEvents();
// }

// void Input_Manager::HandleInputs() {
//     if (IsKeyPressed(GLFW_KEY_SPACE) && audioSystem) {
//         audioSystem->play("assets/audio/click_sounds/hat.wav", 1.0f);
//     }
// }


#include "Input_Manager.h"
#include "Audio_Manager.h"
#include "Game_Session.h"
#include <GLFW/glfw3.h>
#include <iostream>

Input_Manager::Input_Manager(GLFWwindow* win, Audio_Manager* audio)
    : window(win), audio_system(audio) {}

void Input_Manager::Update() {
    glfwPollEvents();
}

void Input_Manager::set_game_session(Game_Session* session) {
    game_session = session;
}



void Input_Manager::Handle_Inputs() {

    bool left_mouse_pressed_now = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (left_mouse_pressed_now && !left_mouse_pressed) {
        // Mouse button was just pressed
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Get window size
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Normalize x and y to range [0, 1]
        float xNorm = static_cast<float>(xpos) / width;
        float yNorm = static_cast<float>(ypos) / height;


        game_session->click_x_y(xNorm, yNorm, glfwGetTime());
    }
    left_mouse_pressed = left_mouse_pressed_now;

}


bool Input_Manager::Is_Key_Pressed(int key) const {
    // std::cout << "Checking if key " << key << " is pressed." << std::endl;
    if (!window) {
        std::cerr << "Error: GLFW window is not initialized." << std::endl;
        return false;
    }
    if (key < 0 || key >= GLFW_KEY_LAST) {
        std::cerr << "Error: Invalid key code " << key << "." << std::endl;
        return false;
    }
    // std::cout << "Key " << key << " is currently " 
    //           << (glfwGetKey(window, key) == GLFW_PRESS ? "pressed" : "not pressed") 
    //           << "." << std::endl; 

              
    return glfwGetKey(window, key) == GLFW_PRESS;
}
