

// #pragma once

// #include <string>
// #include <vector>
// #include <color.h>
// #include <Renderer.h> // Assuming Renderer is defined in this header
// #include <iostream>

// class Renderer;


// class Animation {
// protected:

// public:
//     Renderer* renderer; // stored renderer pointer
//     bool to_remove = false; // Flag to mark for removal
//     float start_time;
//     float end_time;
//     // Renderer* renderer; // stored renderer pointer
//     float x, y;


//     // Animation(Renderer* r) : renderer(r) {}
//     Animation(Renderer* r, float start, float end, float x, float y)
//         : renderer(r), start_time(start), end_time(end), x(x), y(y) {}

//     virtual void render(float current_time) = 0;

//     virtual ~Animation() {} 


// };

// class Text_Fade : public Animation {
//     private:
//         std::string text; // Text to be displayed
//         float size;       // Norm 0 to 1
//         Color color;      // Color of the text

//     public:
//         Text_Fade(Renderer* r, float start, float end, float x, float y,
//                   const std::string& t, float sz, Color c)
//             : Animation(r, start, end, x, y), text(t), size(sz), color(c) {}


//         void render(float current_time) override {
//             renderer->render_text(text, x, y, size, color.r, color.g , color.b );
//         }
// };


// class Animations{

//     private:
//         std::vector<std::unique_ptr<Animation>> animations;

//     public:
//         void add_animation(std::unique_ptr<Animation> animation) {
//             animations.push_back(std::move(animation));
//         }

//         void update(float current_time) {
//             for (auto& anim : animations) {
//                 if(current_time >= anim->end_time) {
//                     anim->to_remove = true; // Mark for removal

//                 }
//             }

//             // remove_finished_animations(); // Clean up finished animations
//         }

//         void remove_finished_animations() {
//             animations.erase(std::remove_if(animations.begin(), animations.end(),
//                 [](const std::unique_ptr<Animation>& anim) {
//                     return anim->to_remove; // Check if marked for removal
//                 }), animations.end());
//         }

//         void render(Renderer& renderer, float current_time) {
//             for (auto& anim : animations) {
//                 // std::cout << "yo im being called"<<current_time << std::endl;
//                 if (!anim->to_remove) { // Only render if not marked for removal
//                     anim->render(current_time);
//                 }
//             }
//         }
// };








// // class Animation {
// // protected:
// //     bool to_remove = false;
// //     float start_time;
// //     float end_time;
// //     float x, y;
// //     Renderer* renderer;

// // public:
// //     Animation(Renderer* r, float start, float end, float x, float y)
// //         : renderer(r), start_time(start), end_time(end), x(x), y(y) {}

// //     virtual void render(float current_time) = 0;
// //     bool is_finished(float current_time) const {
// //         return current_time >= end_time;
// //     }
// //     bool is_marked_for_removal() const {
// //         return to_remove;
// //     }
// //     void mark_for_removal() {
// //         to_remove = true;
// //     }

// //     virtual ~Animation() = default;
// // };



// // class Text_Fade : public Animation {
// // private:
// //     std::string text;
// //     float size;
// //     Color color;
// //     int font_size;

// // public:
// //     Text_Fade(Renderer* r, float start, float end, float x, float y,
// //               const std::string& t, float sz, Color c, int fs)
// //         : Animation(r, start, end, x, y), text(t), size(sz), color(c), font_size(fs) {}

// //     void render(float current_time) override {
// //         float alpha = std::clamp((end_time - current_time) / (end_time - start_time), 0.0f, 1.0f);
// //         renderer->render_text(text, x, y, size, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, alpha);
// //     }
// // };




#pragma once

#include <string>
#include <vector>
#include <memory>
#include <color.h>

class Renderer;  // Forward declaration

class Animation {
protected:
    Renderer* renderer;
    float start_time;
    float end_time;
    float x, y;

public:
    bool to_remove = false;

    Animation(Renderer* r, float start, float end, float x, float y)
        : renderer(r), start_time(start), end_time(end), x(x), y(y) {}

    virtual ~Animation() {}  // Important for polymorphic delete

    virtual void render(float current_time) = 0;

    float get_end_time() const { return end_time; }

    
};

class Text_Fade : public Animation {
private:
    std::string text;
    float size;
    Color color;

public:
    Text_Fade(Renderer* r, float start, float end, float x, float y,
              const std::string& t, float sz, Color c);

    void render(float current_time) override;
};

class Animations {
private:
    std::vector<std::unique_ptr<Animation>> animations;

public:
    void add_animation(std::unique_ptr<Animation> animation);
    void update(float current_time);
    void remove_finished_animations();
    void render(Renderer& renderer, float current_time);
};
