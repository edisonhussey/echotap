

// #include <glad/gl.h>      // your glad header
// #include <GLFW/glfw3.h>

// #include <iostream>

// // Vertex shader source
// const char* vertexShaderSrc = R"(
// #version 330 core
// layout(location = 0) in vec2 aPos;

// void main() {
//     gl_Position = vec4(aPos, 0.0, 1.0);
// }
// )";

// // Fragment shader source
// const char* fragmentShaderSrc = R"(
// #version 330 core
// out vec4 FragColor;

// void main() {
//     FragColor = vec4(0.4, 0.6, 0.9, 1.0); // Light blue color
// }
// )";

// void checkCompileErrors(unsigned int shader, const std::string& type) {
//     int success;
//     char infoLog[512];
//     if (type != "PROGRAM") {
//         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//         if(!success) {
//             glGetShaderInfoLog(shader, 512, NULL, infoLog);
//             std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
//         }
//     } else {
//         glGetProgramiv(shader, GL_LINK_STATUS, &success);
//         if(!success) {
//             glGetProgramInfoLog(shader, 512, NULL, infoLog);
//             std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
//         }
//     }
// }

// int main() {
//     if (!glfwInit()) {
//         std::cerr << "Failed to init GLFW\n";
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window = glfwCreateWindow(800, 600, "Render Square", NULL, NULL);
//     if (!window) {
//         std::cerr << "Failed to create window\n";
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD\n";
//         glfwTerminate();
//         return -1;
//     }

//     // Vertex data for a square (two triangles)
//     float vertices[] = {
//         -0.5f,  0.5f,  // Top-left
//         -0.5f, -0.5f,  // Bottom-left
//          0.5f, -0.5f,  // Bottom-right

//         -0.5f,  0.5f,  // Top-left
//          0.5f, -0.5f,  // Bottom-right
//          0.5f,  0.5f   // Top-right
//     };

//     // Create VBO + VAO
//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     // Bind VAO
//     glBindVertexArray(VAO);

//     // Bind VBO and buffer data
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // Setup vertex attribute pointer (location=0, vec2)
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Unbind VAO (optional)
//     glBindVertexArray(0);

//     // Compile vertex shader
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
//     glCompileShader(vertexShader);
//     checkCompileErrors(vertexShader, "VERTEX");

//     // Compile fragment shader
//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
//     glCompileShader(fragmentShader);
//     checkCompileErrors(fragmentShader, "FRAGMENT");

//     // Link shaders to program
//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     checkCompileErrors(shaderProgram, "PROGRAM");

//     // Clean up shaders as they're linked now
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Set viewport
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);

//     // Render loop
//     while (!glfwWindowShouldClose(window)) {
//         // Clear screen
//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Draw square
//         glUseProgram(shaderProgram);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 6);

//         // Swap buffers and poll events
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // Cleanup
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteProgram(shaderProgram);

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }
// main.cpp

// //workds
// #include <glad/gl.h>      // glad header
// #include <GLFW/glfw3.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// #include <iostream>

// // Vertex shader source
// const char* vertexShaderSrc = R"(
// #version 330 core
// layout(location = 0) in vec2 aPos;
// layout(location = 1) in vec2 aTexCoord;

// out vec2 TexCoord;

// void main() {
//     gl_Position = vec4(aPos, 0.0, 1.0);
//     TexCoord = aTexCoord;
// }
// )";

// // Fragment shader source
// const char* fragmentShaderSrc = R"(
// #version 330 core
// out vec4 FragColor;
// in vec2 TexCoord;

// uniform sampler2D texture1;

// void main() {
//     FragColor = texture(texture1, TexCoord);
// }
// )";

// void checkCompileErrors(unsigned int shader, const std::string& type) {
//     int success;
//     char infoLog[512];
//     if (type != "PROGRAM") {
//         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//         if(!success) {
//             glGetShaderInfoLog(shader, 512, NULL, infoLog);
//             std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
//         }
//     } else {
//         glGetProgramiv(shader, GL_LINK_STATUS, &success);
//         if(!success) {
//             glGetProgramInfoLog(shader, 512, NULL, infoLog);
//             std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
//         }
//     }
// }

// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         std::cerr << "Failed to init GLFW\n";
//         return -1;
//     }

//     // Setup GLFW OpenGL context version (3.3 Core)
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Create window
//     GLFWwindow* window = glfwCreateWindow(800, 600, "Textured Image", NULL, NULL);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window\n";
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     // Load GL functions with glad
//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD\n";
//         glfwTerminate();
//         return -1;
//     }

//     // Vertex data: positions + texture coords
//     float vertices[] = {
//         // positions   // tex coords
//         -1.0f,  1.0f,  0.0f, 1.0f,  // top-left
//         -1.0f, -1.0f,  0.0f, 0.0f,  // bottom-left
//          1.0f, -1.0f,  1.0f, 0.0f,  // bottom-right

//         -1.0f,  1.0f,  0.0f, 1.0f,  // top-left
//          1.0f, -1.0f,  1.0f, 0.0f,  // bottom-right
//          1.0f,  1.0f,  1.0f, 1.0f   // top-right
//     };

//     // Setup buffers and attributes
//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // position attribute
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     // texture coord attribute
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     // Compile shaders
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
//     glCompileShader(vertexShader);
//     checkCompileErrors(vertexShader, "VERTEX");

//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
//     glCompileShader(fragmentShader);
//     checkCompileErrors(fragmentShader, "FRAGMENT");

//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     checkCompileErrors(shaderProgram, "PROGRAM");

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Load texture
//     int imgWidth, imgHeight, nrChannels;
//     stbi_set_flip_vertically_on_load(true);  // flip vertically so it displays correctly
//     unsigned char* data = stbi_load("image.png", &imgWidth, &imgHeight, &nrChannels, 0);
//     if (!data) {
//         std::cerr << "Failed to load texture image.png\n";
//         glfwTerminate();
//         return -1;
//     }

//     unsigned int texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     // Texture wrapping/filtering params
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

//     // Determine format based on number of channels
//     GLenum format = GL_RGB;
//     if (nrChannels == 1)
//         format = GL_RED;
//     else if (nrChannels == 3)
//         format = GL_RGB;
//     else if (nrChannels == 4)
//         format = GL_RGBA;

//     glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
//     glGenerateMipmap(GL_TEXTURE_2D);

//     stbi_image_free(data);

//     // Tell shader which texture unit to use
//     glUseProgram(shaderProgram);
//     glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

//     // Viewport setup
//     int screenWidth, screenHeight;
//     glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//     glViewport(0, 0, screenWidth, screenHeight);

//     // Render loop
//     while (!glfwWindowShouldClose(window)) {
//         // Input
//         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//             glfwSetWindowShouldClose(window, true);

//         // Clear screen
//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Draw textured quad
//         glUseProgram(shaderProgram);
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 6);

//         // Swap buffers and poll IO events
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // Cleanup
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteProgram(shaderProgram);
//     glDeleteTextures(1, &texture);

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }



// #include <glad/gl.h>
// #include <GLFW/glfw3.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// #include <iostream>
// #include <chrono>

// // Vertex shader source (position + tex coords)
// const char* vertexShaderSrc = R"(
// #version 330 core
// layout(location = 0) in vec2 aPos;
// layout(location = 1) in vec2 aTexCoord;

// out vec2 TexCoord;

// void main() {
//     gl_Position = vec4(aPos, 0.0, 1.0);
//     TexCoord = aTexCoord;
// }
// )";

// // Fragment shader source (sample texture)
// const char* fragmentShaderSrc = R"(
// #version 330 core
// out vec4 FragColor;

// in vec2 TexCoord;
// uniform sampler2D spriteTexture;
// uniform float x_offset:
// uniform float y_offset;

// void main() {
//     // Each frame is 1/4th width horizontally
//     vec2 uv = TexCoord;
//     uv.x = uv.x + x_offset;
//     uv.y = uv.y + y_offset;
//     FragColor = texture(spriteTexture, uv);
// }
// )";

// void checkCompileErrors(unsigned int shader, const std::string& type) {
//     int success;
//     char infoLog[512];
//     if (type != "PROGRAM") {
//         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//         if(!success) {
//             glGetShaderInfoLog(shader, 512, NULL, infoLog);
//             std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
//         }
//     } else {
//         glGetProgramiv(shader, GL_LINK_STATUS, &success);
//         if(!success) {
//             glGetProgramInfoLog(shader, 512, NULL, infoLog);
//             std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
//         }
//     }
// }

// int main() {
//     if (!glfwInit()) {
//         std::cerr << "Failed to init GLFW\n";
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window = glfwCreateWindow(800, 600, "Sprite Animation", NULL, NULL);
//     if (!window) {
//         std::cerr << "Failed to create window\n";
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD\n";
//         glfwTerminate();
//         return -1;
//     }

//     // Vertices: positions (x,y) and tex coords (u,v)
//     float vertices[] = {
//         // pos      // tex
//         -0.5f,  0.5f,  0.0f, 1.0f,   // top-left
//         -0.5f, -0.5f,  0.0f, 0.0f,   // bottom-left
//          0.5f, -0.5f,  1.0f, 0.0f,   // bottom-right

//         -0.5f,  0.5f,  0.0f, 1.0f,   // top-left
//          0.5f, -0.5f,  1.0f, 0.0f,   // bottom-right
//          0.5f,  0.5f,  1.0f, 1.0f    // top-right
//     };

//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // pos attribute
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     // tex coord attribute
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glBindVertexArray(0);

//     // Compile shaders
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
//     glCompileShader(vertexShader);
//     checkCompileErrors(vertexShader, "VERTEX");

//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
//     glCompileShader(fragmentShader);
//     checkCompileErrors(fragmentShader, "FRAGMENT");

//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     checkCompileErrors(shaderProgram, "PROGRAM");

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Load texture
//     int imgWidth, imgHeight, nrChannels;
//     stbi_set_flip_vertically_on_load(true); // Flip vertically if needed
//     unsigned char* data = stbi_load("image.png", &imgWidth, &imgHeight, &nrChannels, 0);
//     if (!data) {
//         std::cerr << "Failed to load texture\n";
//         glfwTerminate();
//         return -1;
//     }

//     unsigned int texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     // Texture params
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

//     // Determine format
//     GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

//     glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
//     glGenerateMipmap(GL_TEXTURE_2D);

//     stbi_image_free(data);

//     glUseProgram(shaderProgram);
//     glUniform1i(glGetUniformLocation(shaderProgram, "spriteTexture"), 0);

//     // Animation state
//     int frameCount = 4;
//     int currentFrame = 0;

//     // Timer for frame change (we update frame every render for 60 FPS)
//     auto lastTime = std::chrono::high_resolution_clock::now();

//     // Viewport
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);

//     int counter=0;

//     while (!glfwWindowShouldClose(window)) {
//         // Clear screen
//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Update animation frame every 1/60th second (optional, here every frame)
//         // For demo just increment each frame every render

//         counter++;
//         // if(counter % 30 == 0) {
//         //     counter = 0;
//         //     currentFrame = (currentFrame + 1) % frameCount;
//         // }
//         currentFrame = (currentFrame + 1) % frameCount;
//         // currentFrame = (currentFrame + 1) % frameCount;

//         // Set frameOffset uniform (frame index * 1/4 because 4 frames horizontally)
//         // float frameOffset = (float)currentFrame / (float)frameCount;
//         float 

//         glUseProgram(shaderProgram);
//         glUniform1f(glGetUniformLocation(shaderProgram, "frameOffset"), frameOffset);

//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture);

//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 6);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteProgram(shaderProgram);
//     glDeleteTextures(1, &texture);

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }


#include <glad/gl.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <chrono>

// Vertex Shader
const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

// Fragment Shader with grid frame selection
const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D spriteTexture;
uniform int frameX;
uniform int frameY;
uniform int cols;
uniform int rows;

void main() {
    vec2 frameSize = vec2(1.0 / cols, 1.0 / rows);
    vec2 uv = TexCoord * frameSize;
    uv.x += frameSize.x * frameX;
    uv.y += frameSize.y * frameY;
    FragColor = texture(spriteTexture, uv);
}
)";

void checkCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[512];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Grid Sprite Sheet", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    // Quad vertices with tex coords (cover full sprite frame)
    float vertices[] = {
        // pos       // tex
        -0.5f,  0.5f,  0.0f, 1.0f,  // top-left
        -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right

        -0.5f,  0.5f,  0.0f, 1.0f,  // top-left
         0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f,  1.0f, 1.0f   // top-right
    };

    // VAO/VBO setup
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Compile and link shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load texture
    int imgW, imgH, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgData = stbi_load("image.png", &imgW, &imgH, &channels, 0);
    if (!imgData) {
        std::cerr << "Failed to load image\n";
        return -1;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, imgW, imgH, 0, format, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imgData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

    // Sprite grid info
    const int cols = 4;
    const int rows = 4;
    int currentFrame = 0;

    // Set viewport
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    // Timing
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Animate every 1/10s
        auto now = std::chrono::high_resolution_clock::now();
        float delta = std::chrono::duration<float>(now - lastTime).count();
        if (delta >= 0.016f) {
            currentFrame = (currentFrame + 1) % (cols * rows);
            lastTime = now;
        }

        int frameX = currentFrame % cols;
        int frameY = currentFrame / cols;

        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "spriteTexture"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram, "frameX"), frameX);
        glUniform1i(glGetUniformLocation(shaderProgram, "frameY"), frameY);
        glUniform1i(glGetUniformLocation(shaderProgram, "cols"), cols);
        glUniform1i(glGetUniformLocation(shaderProgram, "rows"), rows);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
