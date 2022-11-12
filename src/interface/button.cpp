#include "../../include/interface/button.h"

Button::Button(const wsdl::Renderer& renderer, const std::string& file_path)
    : Sprite(renderer, file_path) {}

void Button::logic(const Input& input, std::function<void(Button&)> func) {
    if ((input.mouse_x >= getRect().x && input.mouse_x <= getRect().x + getRect().w)
        &&
        (input.mouse_y >= getRect().y && input.mouse_y <= getRect().y + getRect().h)
        &&
        (input.any_mouse_button)
    ) {
        func(*this);
    }
}
