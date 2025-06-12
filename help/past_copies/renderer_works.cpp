

// #include <glad/gl.h>  // Must be first
// #include "Renderer.h"
// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <cmath>
// #include <algorithm>

// #include <ft2build.h>
// #include FT_FREETYPE_H

// #include "Renderer.h"

// std::map<char, Character> Characters;

// bool Renderer::initShaders() {
//     const char* vertexShaderSource = R"(
//     #version 330 core
//     layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
//     out vec2 TexCoords;

//     uniform mat4 projection;

//     void main() {
//         gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
//         TexCoords = vertex.zw;
//     }
//     )";

//     const char* fragmentShaderSource = R"(
//     #version 330 core
//     in vec2 TexCoords;
//     out vec4 color;

//     uniform sampler2D text;
//     uniform vec3 textColor;

//     void main() {
//         float alpha = texture(text, TexCoords).r;
//         color = vec4(textColor, alpha);
//     }
//     )";

//     // Compile vertex shader
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//     glCompileShader(vertexShader);
    
//     // Check for vertex shader compile errors
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
//         std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
//         return false;
//     }

//     // Compile fragment shader
//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//     glCompileShader(fragmentShader);
    
//     // Check for fragment shader compile errors
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
//         std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
//         return false;
//     }

//     // Create shader program and link shaders
//     shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
    
//     // Check for linking errors
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//         std::cerr << "Shader program linking failed: " << infoLog << std::endl;
//         return false;
//     }

//     // Clean up shaders (they're linked now)
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     return true;
// }

// bool Renderer::initFreeType() {
//     FT_Library ft;
//     if (FT_Init_FreeType(&ft)) {
//         std::cerr << "Could not initialize FreeType Library" << std::endl;
//         return false;
//     }

//     FT_Face face;

//     const char* fontPaths[] = {
//         "/System/Library/Fonts/Arial.ttf",                    // Arial - most common
//         "/System/Library/Fonts/Helvetica.ttc",               // Helvetica - always available
//         "/System/Library/Fonts/Times.ttc",                    // Times - backup serif
//         "/System/Library/Fonts/SFNS.ttf",                     // SF Pro - modern macOS
//         "/opt/homebrew/share/fonts/truetype/dejavu/DejaVuSans.ttf", // Homebrew fonts
//         "C:/Windows/Fonts/arial.ttf",                         // Windows fallback (for portability)
//         "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"     // Linux fallback (for portability)
//     };

//     bool fontLoaded = false;
//     for (const char* fontPath : fontPaths) {
//         if (FT_New_Face(ft, fontPath, 0, &face) == 0) {
//             std::cout << "Successfully loaded font: " << fontPath << std::endl;
//             fontLoaded = true;
//             break;
//         }
//     }

//     FT_Set_Pixel_Sizes(face, 0, 48);

//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

//     for (unsigned char c = 0; c < 128; c++) {
//         if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//             std::cerr << "Failed to load Glyph for character: " << c << std::endl;
//             continue;
//         }

//         unsigned int texture;
//         glGenTextures(1, &texture);
//         glBindTexture(GL_TEXTURE_2D, texture);
//         glTexImage2D(
//             GL_TEXTURE_2D,
//             0,
//             GL_RED,
//             face->glyph->bitmap.width,
//             face->glyph->bitmap.rows,
//             0,
//             GL_RED,
//             GL_UNSIGNED_BYTE,
//             face->glyph->bitmap.buffer
//         );

//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//         Character character = {
//             texture,
//             static_cast<int>(face->glyph->bitmap.width),
//             static_cast<int>(face->glyph->bitmap.rows),
//             face->glyph->bitmap_left,
//             face->glyph->bitmap_top,
//             static_cast<unsigned int>(face->glyph->advance.x)
//         };
//         Characters.insert(std::pair<char, Character>(c, character));
//     }

//     FT_Done_Face(face);
//     FT_Done_FreeType(ft);

//     return true;
// }

// Renderer::Renderer(int w, int h)
//     : screenWidth(w), screenHeight(h), window(nullptr), VAO(0), VBO(0), shaderProgram(0)
// {
//     // You can add other initialization here if needed
// }

// Renderer::~Renderer() {
//     // Clean up OpenGL resources
//     if (VAO) glDeleteVertexArrays(1, &VAO);
//     if (VBO) glDeleteBuffers(1, &VBO);
//     if (shaderProgram) glDeleteProgram(shaderProgram);
    
//     // Clean up character textures
//     for (auto& pair : Characters) {
//         glDeleteTextures(1, &pair.second.TextureID);
//     }
//     Characters.clear();
    
//     if (window) {
//         glfwDestroyWindow(window);
//         glfwTerminate();
//     }
// }

// bool Renderer::init() {
//     if (!glfwInit()) {
//         std::cerr << "[Renderer] Failed to initialize GLFW\n";
//         return false;
//     }

//     std::cout << "[Renderer] Starting init...\n";

//     // Set OpenGL version
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); ///compile with compatibility profile
    
//     window = glfwCreateWindow(screenWidth, screenHeight, "osu2", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "[Renderer] Failed to create GLFW window!\n";
//         glfwTerminate();
//         return false;
//     }
//     std::cout << "[Renderer] GLFW window created\n";

//     glfwMakeContextCurrent(window);

//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cerr << "[Renderer] Failed to initialize GLAD\n";
//         return false;
//     }

//     if (!initShaders()) {
//         std::cerr << "Failed to initialize shaders\n";
//         return false;
//     }

//     if (!initFreeType()) {
//         std::cerr << "Failed to initialize FreeType\n";
//         return false;
//     }

//     // Set up VAO and VBO for text rendering
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     std::cout << "[Renderer] GLAD initialized\n";

//     glViewport(0, 0, screenWidth, screenHeight);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     std::cout << "[Renderer] Init completed successfully\n";
//     return true;
// }

// void Renderer::clear() {
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT);
// }

// void Renderer::present() {
//     glfwSwapBuffers(window);
//     glfwPollEvents();
// }

// bool Renderer::should_close() {
//     return glfwWindowShouldClose(window);
// }

// void Renderer::render(const Beatmap& map, float currentTime) {
//     clear();

//     // Disable depth testing for 2D rendering
//     glDisable(GL_DEPTH_TEST);

//     for (const auto& t : map.getTapsInWindow(currentTime - 1.0f, currentTime + 2.0f)) {
//         if (currentTime >= t.start_window && currentTime <= t.end_window) {
//             drawTap(t, currentTime);
//         }
//     }

//     for (const auto& p : map.getPromptsInWindow(currentTime - 1.0f, currentTime + 5.0f)) {
//         if (currentTime >= p.start_window && currentTime <= p.end_window) {
//             draw_prompt(p);
//         }
//     }

//     present();
// }

// void Renderer::draw_circle(float cx, float cy, float r, const std::array<int, 4>& colour, bool filled) {
//     const int segments = 100;
    
//     // Switch to immediate mode for circle drawing (legacy OpenGL)
//     glUseProgram(0); // Use fixed-function pipeline
//     glDisable(GL_TEXTURE_2D);
    
//     glColor4ub(colour[0], colour[1], colour[2], colour[3]);
//     filled ? glBegin(GL_TRIANGLE_FAN) : glBegin(GL_LINE_LOOP);
    
//     for (int i = 0; i <= segments; ++i) {
//         float theta = (2.0f * 3.1415926f * float(i)) / float(segments);
//         float x = r * cosf(theta);
//         float y = r * sinf(theta);
//         glVertex2f((cx + x) / (screenWidth / 2.0f) - 1.0f, 1.0f - (cy + y) / (screenHeight / 2.0f));
//     }
//     glEnd();
// }

// void Renderer::drawTap(const Tap& t, float currentTime) {
//     std::array<int, 4> placeholderColor = {255, 255, 255, 64};

//     float duration = t.end_window - t.start_window;
//     float progression = std::clamp((currentTime - t.start_window) / duration, 0.0f, 1.0f);

//     float outerRadius = t.size * screenWidth * (1 - 0.6f * progression);
//     float innerRadius = t.size * screenWidth * 0.4f;

//     float cx = t.x * screenWidth;
//     float cy = t.y * screenHeight;

//     draw_circle(cx, cy, outerRadius, placeholderColor, false); // outer ring
//     draw_circle(cx, cy, innerRadius + 5, placeholderColor, false); // black inner ring
//     draw_circle(cx, cy, innerRadius, placeholderColor, true); // solid center
// }

// void Renderer::draw_prompt(const Prompt& p) {
//     float cx = p.x * screenWidth;
//     float cy = p.y * screenHeight;

//     // Draw the text near the circle
//     float textX = cx + 25.0f;  // offset right of the circle
//     float textY = cy - 10.0f;  // slight vertical adjustment

//     // Only render text if Characters map is not empty
//     if (!Characters.empty()) {
//         render_text(
//             p.prompt_text,           // The prompt/question text
//             textX,
//             textY,
//             0.5f,             // scale factor (adjust based on desired size)
//             1.0f, 1.0f, 1.0f, // white color
//             screenWidth,
//             screenHeight
//         );
//     }
// }

// void Renderer::render_text(const std::string& text, float x, float y, float scale,
//                            float r, float g, float b, int screenWidth, int screenHeight) {
//     // Check if Characters map is empty
//     if (Characters.empty()) {
//         std::cerr << "Characters map is empty - FreeType not initialized properly" << std::endl;
//         return;
//     }

//     glUseProgram(shaderProgram);
//     glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), r, g, b);

//     glActiveTexture(GL_TEXTURE0);
//     glBindVertexArray(VAO);

//     // Setup orthographic projection matrix based on current screen size
//     float ortho[16] = {
//         2.0f / screenWidth, 0, 0, 0,
//         0, 2.0f / screenHeight, 0, 0,
//         0, 0, -1, 0,
//         -1, -1, 0, 1
//     };
//     glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, ortho);

//     for (auto c : text) {
//         // Check if character exists in the map
//         if (Characters.find(c) == Characters.end()) {
//             std::cerr << "Character '" << c << "' not found in Characters map" << std::endl;
//             continue;
//         }

//         Character ch = Characters[c];

//         float xpos = x + ch.BearingX * scale;
//         float ypos = y - (ch.SizeY - ch.BearingY) * scale;

//         float w = ch.SizeX * scale;
//         float h = ch.SizeY * scale;

//         // Vertices for two triangles forming the quad for this glyph
//         float vertices[6][4] = {
//             { xpos,     ypos + h, 0.0f, 0.0f },
//             { xpos,     ypos,     0.0f, 1.0f },
//             { xpos + w, ypos,     1.0f, 1.0f },

//             { xpos,     ypos + h, 0.0f, 0.0f },
//             { xpos + w, ypos,     1.0f, 1.0f },
//             { xpos + w, ypos + h, 1.0f, 0.0f }
//         };

//         glBindTexture(GL_TEXTURE_2D, ch.TextureID);

//         // Update content of VBO memory
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//         glBindBuffer(GL_ARRAY_BUFFER, 0);

//         // Render glyph quad
//         glDrawArrays(GL_TRIANGLES, 0, 6);

//         // Advance cursor for next glyph (advance is in 1/64 pixels)
//         x += (ch.Advance >> 6) * scale;
//     }

//     glBindVertexArray(0);
//     glBindTexture(GL_TEXTURE_2D, 0);
// }



// #pragma once
// #include "../logical/Beatmap.h"
// #include "../logical/Tap.h"
// #include "../logical/Prompt.h"
// #include <GLFW/glfw3.h>

// // struct Color {
// //     unsigned char r, g, b, a;
// // };

// #include <map>

// struct Character {
//     unsigned int TextureID;
//     int SizeX, SizeY;
//     int BearingX, BearingY;
//     unsigned int Advance;
// };

// extern std::map<char, Character> Characters;


// class Renderer {
// public:
//     Renderer(int w, int h);
//     ~Renderer();

//     bool init();
//     void clear();
//     void present();
//     bool should_close();
//     bool initShaders();
//     bool initFreeType();

//     void render(const Beatmap& map, float currentTime);


//     // void render_text(const std::string& text, float x, float y, float scale, float r, float g, float b); //new

//     void render_text(const std::string& text, float x, float y, float scale, float r, float g, float b, int screenWidth, int screenHeight);

//     bool init_free_type(const std::string& font_path); //new

// private:
//     int screenWidth, screenHeight;
//     GLFWwindow* window;
//     unsigned int VAO, VBO, shaderProgram;//new

//     void drawTap(const Tap& t, float currentTime);
//     void draw_prompt(const Prompt& p);
//     void draw_circle(float cx, float cy, float radius, const std::array<int, 4>& colour, bool filled);

//     // unsigned int VAO, VBO, shaderProgram;//new
// };
