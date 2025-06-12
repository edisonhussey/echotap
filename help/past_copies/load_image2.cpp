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
