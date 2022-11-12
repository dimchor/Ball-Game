#include "../../include/wsdl/wsdl_sprite.h"

wsdl::Sprite::Sprite(const Renderer& renderer, const std::string& file_path) { // add exceptions
    reset(renderer, file_path); 
}

wsdl::Sprite::Sprite(Sprite&& sprite) noexcept : WSDL_Object(std::move(sprite)) {
    moveAttributes(std::move(sprite));
}

wsdl::Sprite& wsdl::Sprite::operator=(Sprite&& sprite) noexcept {
    WSDL_Object::operator=(std::move(sprite));
    moveAttributes(std::move(sprite));
    return *this;
}

wsdl::Sprite::Sprite(const Sprite& sprite) { // add exceptions
    *this = sprite;
}

wsdl::Sprite& wsdl::Sprite::operator=(const Sprite& sprite) { // add exceptions
    copyAttributes(sprite);
    make();
    return *this;
}

bool wsdl::Sprite::make() {
    WSDL_Object::reset(IMG_LoadTexture(renderer->get(), file_path.c_str()));
    if(!get()) {
        return false;
    }
    SDL_QueryTexture(get(), NULL, NULL, &rect.w, &rect.h);
    return true;
}

void wsdl::Sprite::moveAttributes(Sprite&& sprite) noexcept {
    this->renderer = std::exchange(sprite.renderer, nullptr);
    this->file_path = std::move(sprite.file_path);
    this->rect = std::exchange(sprite.rect, { WSDL_DEFAULT_SPRITE_LOCATION, WSDL_DEFAULT_SPRITE_SIZE });
}

void wsdl::Sprite::copyAttributes(const Sprite& sprite) {
    this->renderer = sprite.renderer;
    this->file_path = sprite.file_path;
    this->rect = sprite.rect;
}

const wsdl::Renderer& wsdl::Sprite::getRenderer() const {
    return *renderer;
}

const std::string& wsdl::Sprite::getFilePath() const {
    return file_path;
}

const int& wsdl::Sprite::getX() const {
    return rect.x;
}

const int& wsdl::Sprite::getY() const {
    return rect.y;
}

const int& wsdl::Sprite::getW() const {
    return rect.w;
}

const int& wsdl::Sprite::getH() const {
    return rect.h;
}

const SDL_Rect& wsdl::Sprite::getRect() const {
    return rect;
}

const wsdl::Vector2 wsdl::Sprite::getLocation() const {
    return { rect.x, rect.y };
}

void wsdl::Sprite::setX(const int& x) {
    this->rect.x = x;
}

void wsdl::Sprite::setY(const int& y) {
    this->rect.y = y;
}

void wsdl::Sprite::setRect(const SDL_Rect& rect) {
    this->rect = rect;
}

void wsdl::Sprite::setLocation(const Vector2& location) {
    this->rect.x = location.x;
    this->rect.y = location.y;
}

void wsdl::Sprite::blit() const {
    SDL_RenderCopy(renderer->get(), get(), NULL, &rect);
}

bool wsdl::Sprite::reset(const Renderer& renderer, const std::string& file_path) {
    this->renderer = &renderer;
    this->file_path = file_path;
    return make();
}

bool wsdl::Sprite::resetTexture(const std::string& file_path) {
    this->file_path = file_path;
    return make();
}
