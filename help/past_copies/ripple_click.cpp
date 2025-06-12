
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

struct Ripple {
    float x, y;       // normalized coords (0..1)
    float radius;
    float maxRadius;
    float alpha;
    float speed;
};

std::vector<Ripple> ripples;

// Window size
int winWidth = 800;
int winHeight = 600;

// Vertex shader: pass through position
const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 pos;
out vec2 fragPos;

void main() {
    fragPos = pos;
    gl_Position = vec4(pos, 0.0, 1.0);
}
)";

// Fragment shader: draw circle ripple with smooth edge and fading alpha
const char* fragmentShaderSrc = R"(
#version 330 core
in vec2 fragPos;
out vec4 FragColor;

uniform vec2 rippleCenter;   // normalized coords (-1..1)
uniform float radius;
uniform float alpha;

void main() {
    float dist = distance(fragPos, rippleCenter);
    float thickness = 0.02;
    float edge0 = radius - thickness;
    float edge1 = radius;

    // Smoothstep for smooth edges of the ripple ring
    float ring = smoothstep(edge1, edge0, dist);

    // Output white color with alpha modulated by ring and ripple alpha
    FragColor = vec4(1.0, 1.0, 1.0, ring * alpha);

    if (FragColor.a < 0.01)
        discard; // optimize by discarding transparent pixels
}
)";

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

unsigned int compileShader(unsigned int type, const char* src) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
    }
    return shader;
}

unsigned int createShaderProgram() {
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program linking error: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// Vertex data for a fullscreen quad (two triangles)
float vertices[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
    -1.0f,  1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f
};

unsigned int VAO, VBO;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        // Convert to normalized coordinates (-1..1)
        float nx = (float)(xpos / winWidth) * 2.0f - 1.0f;
        float ny = 1.0f - (float)(ypos / winHeight) * 2.0f; // flip y-axis

        // Add new ripple at this position
        Ripple ripple;
        ripple.x = nx;
        ripple.y = ny;
        ripple.radius = 0.0f;
        ripple.maxRadius = 0.7f;
        ripple.alpha = 1.0f;
        ripple.speed = 0.5f; // units per second
        ripples.push_back(ripple);
    }
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);

    if(!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Ripple Clicks", nullptr, nullptr);
    if(!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    unsigned int shaderProgram = createShaderProgram();

    // Setup VAO/VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float lastTime = (float)glfwGetTime();

    while(!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // Update and render ripples
        for (size_t i = 0; i < ripples.size();) {
            Ripple& r = ripples[i];
            r.radius += r.speed * deltaTime;
            r.alpha = 1.0f - (r.radius / r.maxRadius);

            if (r.alpha <= 0.0f) {
                // Remove ripple when fully faded
                ripples.erase(ripples.begin() + i);
            } else {
                // Set uniforms
                int centerLoc = glGetUniformLocation(shaderProgram, "rippleCenter");
                glUniform2f(centerLoc, r.x, r.y);

                int radiusLoc = glGetUniformLocation(shaderProgram, "radius");
                glUniform1f(radiusLoc, r.radius);

                int alphaLoc = glGetUniformLocation(shaderProgram, "alpha");
                glUniform1f(alphaLoc, r.alpha);

                glDrawArrays(GL_TRIANGLES, 0, 6);
                i++;
            }
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glfwGetFramebufferSize(window, &winWidth, &winHeight);
        glViewport(0, 0, winWidth, winHeight);
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}



