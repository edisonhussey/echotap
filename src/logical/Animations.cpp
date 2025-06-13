#include "Animations.h"
#include "Renderer.h"  // Now we can use Renderer methods
#include "context.h"

Text_Fade::Text_Fade(Renderer* r, float start, float end, float x, float y,
                     const std::string& t, float sz, Color c)
    : Animation(r, start, end, x, y), text(t), size(sz), color(c) {}

void Text_Fade::render(float current_time) {
    // renderer->render_text(text, x*1440, y*900, size, color.r, color.g, color.b);
    renderer->simple_render_text(x, y, text, size, color);

}

// Implement Animations methods too...
void Animations::add_animation(std::unique_ptr<Animation> animation) {
    animations.push_back(std::move(animation));
}

void Animations::update(float current_time) {
    for (auto& anim : animations) {
        if (current_time >= anim->get_end_time()) {
            anim->to_remove = true;
        }
    }

    remove_finished_animations();  // Clean up finished animations
}

void Animations::remove_finished_animations() {
    animations.erase(std::remove_if(animations.begin(), animations.end(),
        [](const std::unique_ptr<Animation>& anim) {
            return anim->to_remove;
        }), animations.end());
}

void Animations::render(Renderer& renderer, float current_time) {
    for (auto& anim : animations) {
        if (!anim->to_remove) {
            anim->render(current_time);
        }
    }
}

Animations::Animations(context* ctx) : ctx(ctx) {}
