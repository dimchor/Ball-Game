#include "../../include/game/bg_pattern.h"

BackgroundPattern::BackgroundPattern(const wsdl::Window& window, const wsdl::Renderer& renderer, const std::string& file_path) 
    : window(&window), renderer(&renderer) {   
    wsdl::Sprite sprite(*(this->renderer), file_path);
    for (int i = 0; i < window.getRect().w; i += sprite.getRect().w) {
        for (int j = 0; j < window.getRect().h; j += sprite.getRect().h) {
            sprite.setLocation({ i, j });
            sprites.push_back(sprite);
        }
    }
    
}

void BackgroundPattern::blit() const {
    for (const auto& sprite : sprites) {
        sprite.blit();
    }
}
