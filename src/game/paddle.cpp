#include "../../include/game/paddle.h"

Paddle::Paddle(const wsdl::Renderer& renderer, std::string assets_dir)
    :Sprite(renderer, assets_dir + "paddle_" + std::to_string(MEDIUM) + ".png"), assets_dir(std::move(assets_dir)) {}

void Paddle::logic(const Input& input) {
    int mouse_x = input.mouse_x;
    if (mouse_x > getRenderer().getWindow().getRect().w - getW()) { // window.width - sprite.width
        mouse_x = getRenderer().getWindow().getRect().w - getW();
    }
    setLocation({ mouse_x,
                  getRenderer().getWindow().getRect().h - getH() - 15 });
}

void Paddle::enlarge() {
    if (size == LARGE) {
        return;
    }
    resetTexture(assets_dir + "paddle_" + std::to_string(++size) + ".png");
}

void Paddle::contract() {
    if (size == SMALL) {
        return;
    }
    resetTexture(assets_dir + "paddle_" + std::to_string(--size) + ".png");
}

void Paddle::reset() {
    size = MEDIUM;
    resetTexture(assets_dir + "paddle_" + std::to_string(MEDIUM) + ".png");
}
