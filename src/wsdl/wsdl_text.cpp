#include "../../include/wsdl/wsdl_text.h"

wsdl::Text::Text(const Renderer& renderer, const std::string& font_location, const unsigned int& font_size) { // add exception
    reset(renderer, font_location, font_size);
}

wsdl::Text::Text(Text&& text) noexcept {
    *this = std::move(text);
}

wsdl::Text& wsdl::Text::operator=(Text&& text) noexcept {
    moveAttributes(std::move(text));
    return *this;
}

wsdl::Text::Text(const Text& text) { // add exception
    *this = text;
}

wsdl::Text& wsdl::Text::operator=(const Text& text) { // add exception
    copyAttributes(text);
    reset(*(text.renderer), text.font_location, text.font_size);
    return *this;
}

wsdl::Text& wsdl::Text::operator=(const char* str) {
    setString(str);
    return *this;
}

wsdl::Text& wsdl::Text::operator=(const std::string& str) {
    setString(str);
    return *this;
}

bool wsdl::Text::make() {
    font.reset(TTF_OpenFont(font_location.c_str(), font_size));
    return isValid(font.get());
}

void wsdl::Text::moveAttributes(Text&& text) noexcept {
    this->renderer = std::exchange(text.renderer, nullptr);
    this->font = std::move(text.font);
    this->surface = std::move(text.surface);
    this->texture = std::move(text.texture);
    this->font_location = std::move(font_location);
    this->font_size = std::exchange(text.font_size, WSDL_DEFAULT_TEXT_FONT_SIZE);
    this->msg = std::exchange(text.msg, WSDL_DEFAULT_TEXT_MSG);
    this->color = std::exchange(text.color, { WSDL_DEFAULT_TEXT_COLOR });
    this->modified = std::exchange(text.modified, WSDL_DEFAULT_TEXT_MODIFIED);
    this->rect = std::exchange(text.rect, { WSDL_DEFAULT_TEXT_LOCATION, WSDL_DEFAULT_TEXT_SIZE });
}

void wsdl::Text::copyAttributes(const Text& text) {
    this->msg = text.msg;
    this->color = text.color;
    this->rect.x = text.rect.x;
    this->rect.y = text.rect.y;
}

TTF_Font* wsdl::Text::get() const {
    return font.get();
}

void wsdl::Text::setString(const std::string& msg) {
    this->msg = msg;
    modified = true;
}

std::string wsdl::Text::getString() const {
    return msg;
}

const int& wsdl::Text::getX() const {
    return rect.x;
}

void wsdl::Text::setX(const int& x) {
    this->rect.x = x;
    modified = true;
}

const int& wsdl::Text::getY() const {
    return rect.y;
}

void wsdl::Text::setY(const int& y) {
    this->rect.y = y;
    modified = true;
}

const int& wsdl::Text::getW() const {
    return rect.w;
}

const int& wsdl::Text::getH() const {
    return rect.h;
}

const SDL_Color& wsdl::Text::getColor() const {
    return color;
}

void wsdl::Text::setLocation(const wsdl::Vector2& location) {
    this->rect.x = location.x;
    this->rect.y = location.y;
    modified = true;
}

void wsdl::Text::setColor(const SDL_Color& color) {
    this->color = color;
    modified = true;
}

void wsdl::Text::print() {
    if (!renderer->get() || !font.get()) {
        return;
    }
    if (modified) { // do this only if no textures were generated or when the text was modified
        modified = false;
        surface.reset(TTF_RenderText_Solid(font.get(), msg.c_str(), color));
        if (!surface.get()) {
            return;
        }
        texture.reset(SDL_CreateTextureFromSurface(renderer->get(), surface.get()));
        if (!texture.get()) {
            return;
        }
        SDL_QueryTexture(texture.get(), NULL, NULL, &rect.w, &rect.h);
    }
    SDL_RenderCopy(renderer->get(), texture.get(), NULL, &rect);
}

bool wsdl::Text::reset(const Renderer& renderer, const std::string& font_location, const unsigned int& font_size) {
    this->renderer = &renderer;
    this->font_location = font_location;
    this->font_size = font_size;
    this->modified = WSDL_DEFAULT_TEXT_MODIFIED;
    return make();
}

