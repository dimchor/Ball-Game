#pragma once

#include "wsdl.h"
#include "wsdl_object.h"
#include "wsdl_window.h"

#define WSDL_DEFAULT_RENDERER_INDEX -1
#define WSDL_DEFAULT_RENDERER_FLAGS 0

namespace wsdl {
    class Renderer : public WSDL_Object<SDL_Renderer> {
        public:
            Renderer(const Window&, const int&, const Uint32&);
            
            Renderer(Renderer&&) = delete; // why would you move this?
            Renderer& operator=(Renderer&&) = delete;
            Renderer(const Renderer&) = delete; // why would you need a second renderer for the same window?
            Renderer& operator=(const Renderer&) = delete;

            const Window& getWindow() const;
            const int& getIndex() const;
            const Uint32& getFlags() const;

            bool reset(const Window&, const int&, const Uint32&);
        private:
            const Window* window { nullptr };
            int index { WSDL_DEFAULT_RENDERER_INDEX };
            Uint32 flags { WSDL_DEFAULT_RENDERER_FLAGS };
            
            bool make();
    };
}

