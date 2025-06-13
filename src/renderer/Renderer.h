



#ifndef RENDERER_H
#define RENDERER_H


#include "../logical/Beatmap.h"
#include "../logical/Tap.h"
#include "../logical/Prompt.h"
#include "Animations.h"
#include <GLFW/glfw3.h>
#include <map>

class Animations;

struct Character {
    unsigned int TextureID;
    int SizeX, SizeY;
    int BearingX, BearingY;
    unsigned int Advance;
};



class Renderer {
private:


    GLFWwindow* window;
    int screenWidth, screenHeight;
    
    // Text rendering
    GLuint textVAO, textVBO;
    GLuint textShaderProgram;
    std::map<char, Character> Characters;

    // Circle rendering
    GLuint circleVAO, circleVBO;
    GLuint circleShaderProgram;

    // For background image
    GLuint bgVAO, bgVBO;
    GLuint bgShaderProgram;
    GLuint bgTexture;



    
    // Shader initialization methods
    bool initTextShaders();
    bool initCircleShaders();
    void setupCircleBuffers();


public:
    Renderer(int w, int h);
    ~Renderer();

    GLFWwindow* get_window() const;

    
    bool init();
    void clear();
    void present();
    bool should_close();
    
    void render(const Beatmap& map, float currentTime, Animations& animations);
    void draw_circle(float cx, float cy, float r, const std::array<int, 4>& colour, bool filled);
    void drawTap(const Tap& t, float currentTime);
    void draw_prompt(const Prompt& p);
    void render_text(const std::string& text, float x, float y, float scale,
                     float r, float g, float b);

    std::pair<float, float> get_pixel_coordinates_text(std::string text, float x, float y, float scale);
    void render_text_2(float pixel_x, float pixel_y, std::string text,float scale, Color color);
    void simple_render_text(float x, float y, const std::string& text, float scale, Color color);

    bool initFreeType();

    bool initBackground(const std::string& backgroundImagePath);
    void renderBackground();
};


#endif // RENDERER_H