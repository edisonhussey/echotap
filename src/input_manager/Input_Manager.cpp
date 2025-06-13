#pragma once
#include "Input_Manager.h"
#include "Audio_Manager.h"
#include "Game_Session.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "context.h"

Input_Manager::Input_Manager(context* ctx)
    : ctx(ctx) {}

void Input_Manager::Update() {
    glfwPollEvents();
}

// void Input_Manager::set_game_session(Game_Session* session) {
//     game_session = session;
// }



void Input_Manager::Handle_Inputs() {
    if (!ctx || !ctx->game_session || !ctx->renderer) {
        std::cerr << "Error: Input_Manager context or game session is not initialized." << std::endl;
        return;
    }
    bool left_mouse_pressed_now = glfwGetMouseButton(ctx->renderer->get_window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (left_mouse_pressed_now && !left_mouse_pressed) {
        // Mouse button was just pressed
        double xpos, ypos;
        glfwGetCursorPos(ctx->renderer->get_window(), &xpos, &ypos);

        // Get window size
        int width, height;
        glfwGetWindowSize(ctx->renderer->get_window(), &width, &height);

        // Normalize x and y to range [0, 1]
        float xNorm = static_cast<float>(xpos) / width;
        float yNorm = static_cast<float>(ypos) / height;


        ctx->game_session->click_x_y(xNorm, yNorm, glfwGetTime());
    }
    left_mouse_pressed = left_mouse_pressed_now;

}


bool Input_Manager::Is_Key_Pressed(int key) const {
    // std::cout << "Checking if key " << key << " is pressed." << std::endl;
    if (!ctx || !ctx->renderer) {
        std::cerr << "Error: Input_Manager context or renderer is not initialized." << std::endl;
        return false;
    }
    if (key < 0 || key >= GLFW_KEY_LAST) {
        std::cerr << "Error: Invalid key code " << key << "." << std::endl;
        return false;
    }
    // std::cout << "Key " << key << " is currently " 
    //           << (glfwGetKey(window, key) == GLFW_PRESS ? "pressed" : "not pressed") 
    //           << "." << std::endl; 

    return glfwGetKey(ctx->renderer->get_window(), key) == GLFW_PRESS;
}
