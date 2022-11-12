#include "../../include/wsdl/wsdl_renderer.h"

wsdl::Renderer::Renderer(const Window& window, const int& index, const Uint32& flags) { // add exception
    reset(window, index, flags); 
}

bool wsdl::Renderer::make() {
    WSDL_Object::reset(SDL_CreateRenderer(window->get(), index, flags));
    return isValid(get());
}

const wsdl::Window& wsdl::Renderer::getWindow() const {
    return *window;
}

const int& wsdl::Renderer::getIndex() const {
    return index;
}

const Uint32& wsdl::Renderer::getFlags() const {
    return flags;
}

bool wsdl::Renderer::reset(const Window& window, const int& index, const Uint32& flags) {
    this->window = &window;
    this->index = index;
    this->flags = flags;
    return make(); 
}
