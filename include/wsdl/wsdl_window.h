#pragma once

#include "wsdl.h"
#include "wsdl_object.h"

#define WSDL_DEFAULT_WINDOW_TITLE "Window"
#define WSDL_DEFAULT_WINDOW_LOCATION 0, 0
#define WSDL_DEFAULT_WINDOW_SIZE 250, 250
#define WSDL_DEFAULT_WINDOW_FLAGS 0

namespace wsdl {
    class Window : public WSDL_Object<SDL_Window> {
        public:
            Window() = default;
            Window(const std::string&, const SDL_Rect&, const Uint32&);
            Window(Window&&) noexcept;
            Window& operator=(Window&&) noexcept;
            Window(const Window&);
            Window& operator=(const Window&);
            
            bool spawn();
            void despawn();
            bool respawn();
            
            const std::string& getTitle() const;
            const SDL_Rect& getRect() const;
            const Uint32& getFlags() const;
            void setTitle(const std::string&);
            void setRect(const SDL_Rect&);
            void setFlags(const Uint32&); 
        private:
            std::string title { WSDL_DEFAULT_WINDOW_TITLE };
            SDL_Rect rect { WSDL_DEFAULT_WINDOW_LOCATION, WSDL_DEFAULT_WINDOW_SIZE };
            Uint32 flags { WSDL_DEFAULT_WINDOW_FLAGS }; // SDL Flags
            
            void moveAttributes(Window&&) noexcept;
            void copyAttributes(const Window&);
    };
}

