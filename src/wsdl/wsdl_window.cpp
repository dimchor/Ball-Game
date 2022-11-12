#include "../../include/wsdl/wsdl_window.h"

wsdl::Window::Window(const std::string& title, const SDL_Rect& rect, const Uint32& flags) {
    setTitle(title);
    //setLocation(location);
    //setSize(size);
    setRect(rect);
    setFlags(flags);
}

wsdl::Window::Window(Window&& window) noexcept : WSDL_Object(std::move(window)) {
    moveAttributes(std::move(window));
}

wsdl::Window& wsdl::Window::operator=(Window&& window) noexcept {
    WSDL_Object::operator=(std::move(window));
    moveAttributes(std::move(window));
    return *this;
}

wsdl::Window::Window(const Window& window) {
    copyAttributes(window);
}

wsdl::Window& wsdl::Window::operator=(const Window& window) {
    copyAttributes(window);
    return *this;
}

bool wsdl::Window::spawn() {
    reset(SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, flags));
    return isValid(get());
}

void wsdl::Window::despawn() {
    WSDL_Object::reset();
}

bool wsdl::Window::respawn() {
    despawn();
    return spawn();
}

void wsdl::Window::moveAttributes(Window&& window) noexcept {
    this->title = std::exchange(window.title, WSDL_DEFAULT_WINDOW_TITLE);
    //this->location = std::exchange(window.location, { WSDL_DEFAULT_WINDOW_LOCATION });
    //this->size = std::exchange(window.size, { WSDL_DEFAULT_WINDOW_SIZE });
    this->rect = std::exchange(window.rect, { WSDL_DEFAULT_WINDOW_LOCATION, WSDL_DEFAULT_WINDOW_SIZE });
    this->flags = std::exchange(window.flags, WSDL_DEFAULT_WINDOW_FLAGS);
}

void wsdl::Window::copyAttributes(const Window& window) {
    this->title = window.title;
    //this->location = window.location;
    //this->size = window.size;
    this->rect = window.rect;
    this->flags = window.flags;
}

const std::string& wsdl::Window::getTitle() const {
    return title;
}
/*
const wsdl::Location& wsdl::Window::getLocation() const {
    return location;
}

const wsdl::Size& wsdl::Window::getSize() const {
    return size;
}
*/

const SDL_Rect& wsdl::Window::getRect() const {
    return rect;
}

const Uint32& wsdl::Window::getFlags() const {
    return flags;
}

void wsdl::Window::setTitle(const std::string& title) {
    this->title = title;
}

void wsdl::Window::setRect(const SDL_Rect& rect) {
    this->rect = rect;
}

void wsdl::Window::setFlags(const Uint32& flags) {
    this->flags = flags;
}

