

#include <glad/gl.h>  // Must be first
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



bool Renderer::initBackground(const std::string& imagePath) {
    // Vertex data for fullscreen quad
    float vertices[] = {
        // positions   // tex coords
        -1.0f,  1.0f,  0.0f, 1.0f,  // top-left
        -1.0f, -1.0f,  0.0f, 0.0f,  // bottom-left
         1.0f, -1.0f,  1.0f, 0.0f,  // bottom-right

        -1.0f,  1.0f,  0.0f, 1.0f,  // top-left
         1.0f, -1.0f,  1.0f, 0.0f,  // bottom-right
         1.0f,  1.0f,  1.0f, 1.0f   // top-right
    };

    // Setup VAO/VBO
    glGenVertexArrays(1, &bgVAO);
    glGenBuffers(1, &bgVBO);
    glBindVertexArray(bgVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Shader sources
    const char* vertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 TexCoord;
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D texture1;
        void main() {
            FragColor = texture(texture1, TexCoord);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    bgShaderProgram = glCreateProgram();
    glAttachShader(bgShaderProgram, vertexShader);
    glAttachShader(bgShaderProgram, fragmentShader);
    glLinkProgram(bgShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load image
    int imgWidth, imgHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(imagePath.c_str(), &imgWidth, &imgHeight, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load background image: " << imagePath << std::endl;
        return false;
    }

    GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
    glGenTextures(1, &bgTexture);
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Texture params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return true;
}

void Renderer::renderBackground() {
    glUseProgram(bgShaderProgram);
    glBindVertexArray(bgVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}



bool Renderer::initTextShaders() {
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
    out vec2 TexCoords;

    uniform mat4 projection;

    void main() {
        gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
        TexCoords = vertex.zw;
    }
    )";

    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoords;
    out vec4 color;

    uniform sampler2D text;
    uniform vec3 textColor;

    void main() {
        float alpha = texture(text, TexCoords).r;
        color = vec4(textColor, alpha);
    }
    )";

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    // Check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Text vertex shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Text fragment shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    // Create shader program and link shaders
    textShaderProgram = glCreateProgram();
    glAttachShader(textShaderProgram, vertexShader);
    glAttachShader(textShaderProgram, fragmentShader);
    glLinkProgram(textShaderProgram);
    
    // Check for linking errors
    glGetProgramiv(textShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(textShaderProgram, 512, nullptr, infoLog);
        std::cerr << "Text shader program linking failed: " << infoLog << std::endl;
        return false;
    }

    // Clean up shaders (they're linked now)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Renderer::initCircleShaders() {
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec2 position;
    
    uniform mat4 projection;
    uniform vec2 center;
    uniform float radius;
    
    out vec2 fragPos;
    
    void main() {
        vec2 worldPos = center + position * radius;
        gl_Position = projection * vec4(worldPos, 0.0, 1.0);
        fragPos = position;
    }
    )";

    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 fragPos;
    out vec4 fragColor;
    
    uniform vec4 color;
    uniform bool filled;
    uniform float innerRadius;
    
    void main() {
        float dist = length(fragPos);
        
        if (filled) {
            if (dist > 1.0) {
                discard;
            }
            fragColor = color;
        } else {
            // Ring rendering
            if (dist > 1.0 || dist < innerRadius) {
                discard;
            }
            
            // Anti-aliasing
            float outerEdge = 1.0 - smoothstep(0.95, 1.0, dist);
            float innerEdge = smoothstep(innerRadius - 0.05, innerRadius, dist);
            
            float alpha = outerEdge * innerEdge;
            fragColor = vec4(color.rgb, color.a * alpha);
        }
    }
    )";

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Circle vertex shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Circle fragment shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    // Create and link program
    circleShaderProgram = glCreateProgram();
    glAttachShader(circleShaderProgram, vertexShader);
    glAttachShader(circleShaderProgram, fragmentShader);
    glLinkProgram(circleShaderProgram);
    
    glGetProgramiv(circleShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(circleShaderProgram, 512, nullptr, infoLog);
        std::cerr << "Circle shader program linking failed: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Renderer::setupCircleBuffers() {
    // Create a quad that covers [-1, 1] in both dimensions
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
    };

    glGenVertexArrays(1, &circleVAO);
    glGenBuffers(1, &circleVBO);

    glBindVertexArray(circleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



bool Renderer::initFreeType() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Could not initialize FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;

    const char* fontPaths[] = {
        "/System/Library/Fonts/Arial.ttf",                    // Arial - most common
        "/System/Library/Fonts/Helvetica.ttc",               // Helvetica - always available
        "/System/Library/Fonts/Times.ttc",                    // Times - backup serif
        "/System/Library/Fonts/SFNS.ttf",                     // SF Pro - modern macOS
        "/opt/homebrew/share/fonts/truetype/dejavu/DejaVuSans.ttf", // Homebrew fonts
        "C:/Windows/Fonts/arial.ttf",                         // Windows fallback (for portability)
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"     // Linux fallback (for portability)
    };

    bool fontLoaded = false;
    for (const char* fontPath : fontPaths) {
        if (FT_New_Face(ft, fontPath, 0, &face) == 0) {
            std::cout << "Successfully loaded font: " << fontPath << std::endl;
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded) {
        std::cerr << "Failed to load any font!" << std::endl;
        FT_Done_FreeType(ft);
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "Failed to load Glyph for character: " << c << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            static_cast<int>(face->glyph->bitmap.width),
            static_cast<int>(face->glyph->bitmap.rows),
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

Renderer::Renderer(int w, int h)
    : screenWidth(w), screenHeight(h), window(nullptr), 
      textVAO(0), textVBO(0), textShaderProgram(0),
      circleVAO(0), circleVBO(0), circleShaderProgram(0)
{
    // Constructor initialization
}

Renderer::~Renderer() {
    // Clean up OpenGL resources
    if (textVAO) glDeleteVertexArrays(1, &textVAO);
    if (textVBO) glDeleteBuffers(1, &textVBO);
    if (textShaderProgram) glDeleteProgram(textShaderProgram);
    
    if (circleVAO) glDeleteVertexArrays(1, &circleVAO);
    if (circleVBO) glDeleteBuffers(1, &circleVBO);
    if (circleShaderProgram) glDeleteProgram(circleShaderProgram);
    
    // Clean up character textures
    for (auto& pair : Characters) {
        glDeleteTextures(1, &pair.second.TextureID);
    }
    Characters.clear();
    
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

bool Renderer::init() {
    if (!glfwInit()) {
        std::cerr << "[Renderer] Failed to initialize GLFW\n";
        return false;
    }

    std::cout << "[Renderer] Starting init...\n";

    // Set OpenGL version - keep core profile for modern OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "osu2", nullptr, nullptr);
    if (!window) {
        std::cerr << "[Renderer] Failed to create GLFW window!\n";
        glfwTerminate();
        return false;
    }
    std::cout << "[Renderer] GLFW window created\n";

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "[Renderer] Failed to initialize GLAD\n";
        return false;
    }

    // Initialize text shaders
    if (!initTextShaders()) {
        std::cerr << "Failed to initialize text shaders\n";
        return false;
    }

    // Initialize circle shaders
    if (!initCircleShaders()) {
        std::cerr << "Failed to initialize circle shaders\n";
        return false;
    }

    if (!initFreeType()) {
        std::cerr << "Failed to initialize FreeType\n";
        return false;
    }

    // Set up VAO and VBO for text rendering
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);

    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set up circle rendering buffers
    setupCircleBuffers();

    std::cout << "[Renderer] GLAD initialized\n";

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    std::cout << "[Renderer] Init completed successfully\n";
    return true;
}

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow* Renderer::get_window() const {
    return window;
}


void Renderer::present() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Renderer::should_close() {
    return glfwWindowShouldClose(window);
}

void Renderer::render(const Beatmap& map, float currentTime) {
    clear();

    // Disable depth testing for 2D rendering
    glDisable(GL_DEPTH_TEST);

    renderBackground();

    for (const auto& t : map.getTapsInWindow(currentTime - 1.0f, currentTime + 2.0f)) {
        if (currentTime >= t.start_window && currentTime <= t.end_window) {
            drawTap(t, currentTime);
        }
    }

    for (const auto& p : map.getPromptsInWindow(currentTime - 1.0f, currentTime + 5.0f)) {
        if (currentTime >= p.start_window && currentTime <= p.end_window) {
            draw_prompt(p);
        }
    }

    present();
}

void Renderer::draw_circle(float cx, float cy, float r, const std::array<int, 4>& colour, bool filled) {  //fully wokring
    glUseProgram(circleShaderProgram);
    
    // Set up projection matrix (orthographic, flipped Y for screen coordinates)
    float ortho[16] = {
        2.0f / screenWidth, 0, 0, 0,
        0, -2.0f / screenHeight, 0, 0,  // Negative to flip Y
        0, 0, -1, 0,
        -1, 1, 0, 1  // Adjusted for flipped Y
    };
    glUniformMatrix4fv(glGetUniformLocation(circleShaderProgram, "projection"), 1, GL_FALSE, ortho);
    
    // Set uniforms
    glUniform2f(glGetUniformLocation(circleShaderProgram, "center"), cx, cy);
    glUniform1f(glGetUniformLocation(circleShaderProgram, "radius"), r);
    glUniform4f(glGetUniformLocation(circleShaderProgram, "color"), 
                colour[0]/255.0f, colour[1]/255.0f, colour[2]/255.0f, colour[3]/255.0f);
    glUniform1i(glGetUniformLocation(circleShaderProgram, "filled"), filled ? 1 : 0);

    // glUniform1f(glGetUniformLocation(circleShaderProgram, "innerRadius"), filled ? 0.0f : 0.7f);// was too thick

    
    float ringInnerRadius = 0.9f;  // Try values between 0.7 and 1.0 to adjust thickness
    glUniform1f(glGetUniformLocation(circleShaderProgram, "innerRadius"), filled ? 0.0f : ringInnerRadius);

    glBindVertexArray(circleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void Renderer::drawTap(const Tap& t, float currentTime) {
    std::array<int, 4> placeholderColor = {255, 255, 255, 128}; // More visible alpha

    float duration = t.end_window - t.start_window;
    float progression = std::clamp((currentTime - t.start_window) / duration, 0.0f, 1.0f);

    float outerRadius = t.size * screenWidth * (1 - 0.6f * progression);
    float innerRadius = t.size * screenWidth * 0.4f;

    

    float cx = t.x * screenWidth;
    float cy = t.y * screenHeight;

    // Draw outer ring
    draw_circle(cx, cy, outerRadius, placeholderColor, false);
    
    // Draw inner filled circle
    // std::array<int, 4> innerColor = t.color;
    std::array<int, 4> innerColor = { t.color.r, t.color.g, t.color.b, t.color.a };

    draw_circle(cx, cy, innerRadius, innerColor, true);



    if (!t.text.empty()) {
        float scale = 0.5f;

        // Calculate text width and height in pixels (scaled)
        float textWidth = 0.0f;
        float textHeight = 0.0f;

        for (auto c : t.text) {
            auto it = Characters.find(c);
            if (it != Characters.end()) {
                Character ch = it->second;
                textWidth += (ch.Advance >> 6) * scale;
                float charHeight = ch.SizeY * scale;
                if (charHeight > textHeight) textHeight = charHeight;
            }
        }

        // Center text at (cx, cy)
        float textX = cx - textWidth / 2.0f;
        float textY = cy + textHeight / 2.0f;  // Adjust this if your baseline is different

        render_text(
            t.text,
            textX,
            textY,
            scale,
            1.0f, 1.0f, 1.0f,  // white color
            screenWidth,
            screenHeight
        );
    }

}


void Renderer::render_text(const std::string& text, float x, float y, float scale, 
                          float r, float g, float b, int screenWidth, int screenHeight) {
    glUseProgram(textShaderProgram);
    
    // Use the SAME projection matrix as circles
    float ortho[16] = {
        2.0f / screenWidth, 0, 0, 0,
        0, -2.0f / screenHeight, 0, 0,  // Negative to flip Y
        0, 0, -1, 0,
        -1, 1, 0, 1  // Adjusted for flipped Y
    };
    glUniformMatrix4fv(glGetUniformLocation(textShaderProgram, "projection"), 1, GL_FALSE, ortho);
    
    // Set text color
    glUniform3f(glGetUniformLocation(textShaderProgram, "textColor"), r, g, b);
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    float currentX = x;
    
    for (auto c : text) {
        auto it = Characters.find(c);
        if (it == Characters.end()) continue;
        
        Character ch = it->second;

        float xpos = currentX + ch.BearingX * scale;
        // Fixed baseline - use y as the baseline and adjust each character relative to it
        float ypos = y - ch.BearingY * scale;

        float w = ch.SizeX * scale;
        float h = ch.SizeY * scale;

        // Vertices in screen pixel coordinates with flipped texture coordinates
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos,     ypos,       0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        currentX += (ch.Advance >> 6) * scale;
    }
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_prompt(const Prompt& p) {
    float cx = p.x * screenWidth;
    float cy = (p.y) * screenHeight;  //open gl uses 0,0 as bottom left so we flip the y coordinate

    // Draw the text near the circle
    float textX = cx; // offset right of the circle
    float textY = cy;  // slight vertical adjustment

    // Only render text if Characters map is not empty
    if (!Characters.empty()) {
        render_text(
            p.prompt_text,           // The prompt/question text
            textX,
            textY,
            0.5f,             // scale factor (adjust based on desired size)
            1.0f, 1.0f, 1.0f, // white color
            screenWidth,
            screenHeight
        );
    }
}

