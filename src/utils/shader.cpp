// #include <GL/glew.h> // Or glad, if you're using that
// #include <fstream>
// #include <sstream>
// #include <iostream>

// // Utility to load, compile, and link vertex & fragment shaders
// GLuint LoadShaderProgram(const char* vertexPath, const char* fragmentPath) {
//     // 1. Read shader source files
//     std::ifstream vShaderFile(vertexPath);
//     std::ifstream fShaderFile(fragmentPath);

//     if (!vShaderFile || !fShaderFile) {
//         std::cerr << "Failed to open shader files: "
//                   << vertexPath << ", " << fragmentPath << std::endl;
//         return 0;
//     }

//     std::stringstream vShaderStream, fShaderStream;
//     vShaderStream << vShaderFile.rdbuf();
//     fShaderStream << fShaderFile.rdbuf();
//     std::string vertexCode = vShaderStream.str();
//     std::string fragmentCode = fShaderStream.str();

//     const char* vShaderCode = vertexCode.c_str();
//     const char* fShaderCode = fragmentCode.c_str();

//     // 2. Compile shaders
//     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
//     glCompileShader(vertexShader);
    
//     GLint success;
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
//         std::cerr << "Vertex Shader compilation failed:\n" << infoLog << std::endl;
//         return 0;
//     }

//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
//     glCompileShader(fragmentShader);
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
//         std::cerr << "Fragment Shader compilation failed:\n" << infoLog << std::endl;
//         return 0;
//     }

//     // 3. Link shaders into program
//     GLuint shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
    
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//         std::cerr << "Shader Program linking failed:\n" << infoLog << std::endl;
//         return 0;
//     }

//     // 4. Cleanup
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     return shaderProgram;
// }
