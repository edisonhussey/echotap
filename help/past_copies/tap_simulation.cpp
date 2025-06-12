
// // Globals for window size
// int windowWidth = 800;
// int windowHeight = 600;

// // Convert normalized coordinates (0-1) to screen pixels
// float normToScreenX(float x) {
//     return x * windowWidth;
// }
// float normToScreenY(float y) {
//     return (1.0f - y) * windowHeight; // invert Y since OpenGL bottom-left is (0,0)
// }

// // Draw filled circle at pixel coordinates with radius in pixels and color RGBA (0-255)
// void drawCircle(float cx, float cy, float r, Color col) {
//     const int num_segments = 64;
//     glColor4ub(col.r, col.g, col.b, col.a);
//     glBegin(GL_TRIANGLE_FAN);
//     glVertex2f(cx, cy);
//     for(int i = 0; i <= num_segments; i++) {
//         float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
//         float x = r * cosf(theta);
//         float y = r * sinf(theta);
//         glVertex2f(cx + x, cy + y);
//     }
//     glEnd();
// }

// // Check if point (mx,my) in pixels is inside circle (cx, cy, radius)
// bool pointInCircle(float mx, float my, float cx, float cy, float radius) {
//     float dx = mx - cx;
//     float dy = my - cy;
//     return (dx*dx + dy*dy) <= (radius * radius);
// }

// int main() {
//     if (!glfwInit()) {
//         std::cerr << "Failed to init GLFW\n";
//         return -1;
//     }

//     GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Beatmap Circles", nullptr, nullptr);
//     if (!window) {
//         glfwTerminate();
//         std::cerr << "Failed to create window\n";
//         return -1;
//     }

//     glfwMakeContextCurrent(window);

//     // Set up orthographic projection (2D) matching window size
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     // Example beatmap data with 3 taps
//     std::vector<tap> taps = {
//         {0.3f, 0.5f, 1.0f, 4.0f, 2.5f, -1.0f, 0, 0, true, 80.0f, 0, "Tap 1", {255,255,255,128}},
//         {0.7f, 0.4f, 3.0f, 6.0f, 4.5f, -1.0f, 0, 0, true, 60.0f, 0, "Tap 2", {255,255,255,128}},
//         {0.5f, 0.7f, 5.0f, 8.0f, 6.5f, -1.0f, 0, 0, true, 100.0f, 0, "Tap 3", {255,255,255,128}},
//         {0.3f, 0.5f, 1.0f, 4.0f, 2.5f, -1.0f, 0, 0, true, 80.0f, 0, "Tap 1", {255,255,255,128}},
//         {0.7f, 0.4f, 3.0f, 6.0f, 4.5f, -1.0f, 0, 0, true, 60.0f, 0, "Tap 2", {255,255,255,128}},
//         {0.5f, 0.7f, 5.0f, 8.0f, 6.5f, -1.0f, 0, 0, true, 100.0f, 0, "Tap 3", {255,255,255,128}},
//         {0.3f, 0.5f, 1.0f, 4.0f, 2.5f, -1.0f, 0, 0, true, 80.0f, 0, "Tap 1", {255,255,255,128}},
//         {0.7f, 0.4f, 3.0f, 6.0f, 4.5f, -1.0f, 0, 0, true, 60.0f, 0, "Tap 2", {255,255,255,128}},
//         {0.5f, 0.7f, 5.0f, 8.0f, 6.5f, -1.0f, 0, 0, true, 100.0f, 0, "Tap 3", {255,255,255,128}},
//         {0.3f, 0.5f, 1.0f, 4.0f, 2.5f, -1.0f, 0, 0, true, 80.0f, 0, "Tap 1", {255,255,255,128}},
//         {0.7f, 0.4f, 3.0f, 6.0f, 4.5f, -1.0f, 0, 0, true, 60.0f, 0, "Tap 2", {255,255,255,128}},
//         {0.5f, 0.7f, 5.0f, 8.0f, 6.5f, -1.0f, 0, 0, true, 100.0f, 0, "Tap 3", {255,255,255,128}},
//     };

//     std::vector<prompt> prompts; // empty for now

//     beatmap map(taps, prompts);

//     auto startTimePoint = std::chrono::steady_clock::now();

//     // For mouse click
//     double mouseX, mouseY;

//     // Lambda to get current elapsed time in seconds
//     auto getTime = [&]() -> float {
//         auto now = std::chrono::steady_clock::now();
//         return std::chrono::duration<float>(now - startTimePoint).count();
//     };

//     // Mouse button callback to detect hits
//     glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods){
//         if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//             double mx, my;
//             glfwGetCursorPos(w, &mx, &my);

//             beatmap* mapPtr = (beatmap*)glfwGetWindowUserPointer(w);
//             float timeNow = glfwGetTime(); // fallback if needed

//             if (mapPtr) {
//                 float currentTime = 0.0f;
//                 // We cannot use getTime lambda here, so store currentTime in user pointer or handle differently
//                 // Let's just simulate by reading system steady clock
//                 static auto lastStart = std::chrono::steady_clock::now();
//                 auto now = std::chrono::steady_clock::now();
//                 currentTime = std::chrono::duration<float>(now - lastStart).count();

//                 // Iterate taps active now, check if click inside radius and time window
//                 for (auto& t : mapPtr->taps) {
//                     if (t.actual_hit_time < 0 && currentTime >= t.start_window && currentTime <= t.end_window) {
//                         float cx = normToScreenX(t.x);
//                         float cy = normToScreenY(t.y);

//                         // Compute radius shrinking from size to target radius (say 20 px)
//                         float progress = (currentTime - t.start_window) / (t.end_window - t.start_window);
//                         if (progress < 0) progress = 0;
//                         if (progress > 1) progress = 1;
//                         float radius = t.size * (1.0f - progress) + 20.0f * progress;

//                         if (pointInCircle((float)mx, (float)my, cx, cy, radius)) {
//                             t.actual_hit_time = currentTime;
//                             t.is_correct = true; // simplification
//                             t.color = {0, 255, 0, 255}; // green on hit
//                             std::cout << "Hit tap at time: " << currentTime << "\n";
//                             break; // only one hit per click
//                         }
//                     }
//                 }
//             }
//         }
//     });

//     // Set user pointer for callbacks
//     glfwSetWindowUserPointer(window, &map);

//     while (!glfwWindowShouldClose(window)) {
//         float currentTime = getTime();

//         glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Draw taps active in the current time window +/- 1 second buffer
//         auto activeTaps = map.getTapsInWindow(currentTime - 1.0f, currentTime + 1.0f);

//         for (auto& t : activeTaps) {
//             float cx = normToScreenX(t.x);
//             float cy = normToScreenY(t.y);

//             float progress = (currentTime - t.start_window) / (t.end_window - t.start_window);
//             if (progress < 0) progress = 0;
//             if (progress > 1) progress = 1;

//             // Radius shrinks from t.size to 20 px
//             float radius = t.size * (1.0f - progress) + 20.0f * progress;

//             Color col = t.color;
//             if (t.actual_hit_time >= 0) {
//                 // Already hit: keep green or red based on is_correct
//                 col = t.is_correct ? Color{0,255,0,255} : Color{255,0,0,255};
//             } else if (progress >= 1.0f) {
//                 // Missed (time passed without hit)
//                 col = Color{255,0,0,128};
//             }

//             drawCircle(cx, cy, radius, col);
//         }

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }
