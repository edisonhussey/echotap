
// bool Renderer::init() {


//     if (!glfwInit()) {
//         std::cerr << "GLFW Init Failed!" << std::endl;
//         return false;
//     }

//     window = glfwCreateWindow(screenWidth, screenHeight, "Beatmap Viewer", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window!" << std::endl;
//         glfwTerminate();
//         return false;
//     }

//     glfwMakeContextCurrent(window);
//     glViewport(0, 0, screenWidth, screenHeight);

//     glEnable(GL_BLEND); ///changes
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); ///changes 


//     return true;
// }


// bool Renderer::init() {
//     if (!glfwInit()) {
//         std::cerr << "GLFW Init Failed!" << std::endl;
//         return false;
//     }

//     std::cout << "GLAD initialized, OpenGL version: " << glGetString(GL_VERSION) << std::endl;


//     window = glfwCreateWindow(screenWidth, screenHeight, "Beatmap Viewer", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window!" << std::endl;
//         glfwTerminate();
//         return false;
//     }

//     glfwMakeContextCurrent(window);

//     // Initialize glad here:
//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return false;
//     }

//     glViewport(0, 0, screenWidth, screenHeight);

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     return true;
// }


// bool Renderer::init() {
//     // ... your existing init code ...
//     window = glfwCreateWindow(screenWidth, screenHeight, "Beatmap Viewer", nullptr, nullptr);
//         if (!window) {
//             std::cerr << "Failed to create GLFW window!" << std::endl;
//             glfwTerminate();
//             return false;
//         }

//         glfwMakeContextCurrent(window);  

//     // Load glad
//     if (!gladLoadGL(glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return false;
//     }

//     glViewport(0, 0, screenWidth, screenHeight);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     // -- Shader sources (minimal text shader)
//     const char* vertexShaderSource = R"glsl(
//         #version 330 core
//         layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
//         out vec2 TexCoords;
//         uniform mat4 projection;
//         void main() {
//             gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
//             TexCoords = vertex.zw;
//         }
//     )glsl";

//     const char* fragmentShaderSource = R"glsl(
//         #version 330 core
//         in vec2 TexCoords;
//         out vec4 color;
//         uniform sampler2D text;
//         uniform vec3 textColor;
//         void main() {
//             float alpha = texture(text, TexCoords).r;
//             color = vec4(textColor, alpha);
//         }
//     )glsl";

//     // Compile vertex shader
//     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//     glCompileShader(vertexShader);
//     // Check for errors omitted for brevity

//     // Compile fragment shader
//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//     glCompileShader(fragmentShader);
//     // Check for errors omitted for brevity

//     // Link program
//     shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     // Check for errors omitted for brevity

//     // Delete shaders after linking
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Generate VAO/VBO for text quads
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     return true;
// }