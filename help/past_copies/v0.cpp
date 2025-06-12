

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

