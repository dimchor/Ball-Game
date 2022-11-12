#pragma once

#include "wsdl.h"
#include "wsdl_renderer.h"

#define WSDL_DEFAULT_TEXT_FONT_SIZE 20
#define WSDL_DEFAULT_TEXT_MSG "Hello, World!"
#define WSDL_DEFAULT_TEXT_COLOR 0, 0, 0
#define WSDL_DEFAULT_TEXT_MODIFIED true
#define WSDL_DEFAULT_TEXT_LOCATION 0, 0
#define WSDL_DEFAULT_TEXT_SIZE 0, 0 

namespace wsdl {
    class Text {
        public:
            Text() = default;
            Text(const Renderer&, const std::string&, const unsigned int&);
            Text(Text&&) noexcept;
            Text& operator=(Text&&) noexcept;
            Text(const Text&);
            Text& operator=(const Text&);
            
            Text& operator=(const char*);
            Text& operator=(const std::string&);
            
            TTF_Font* get() const;
            std::string getString() const;
            const int& getX() const;
            const int& getY() const;
            const int& getW() const;
            const int& getH() const;
            const SDL_Rect& getRect() const;
            const SDL_Color& getColor() const;
            void setString(const std::string&);
            void setX(const int&);
            void setY(const int&);
            void setLocation(const Vector2&);
            void setColor(const SDL_Color&);

            void print();
            
            bool reset(const Renderer&, const std::string&, const unsigned int&);
        private:
            const Renderer* renderer { nullptr };
            font_ptr font { nullptr };
            surface_ptr surface { nullptr };
            texture_ptr texture { nullptr };

            std::string font_location {};
            unsigned int font_size { WSDL_DEFAULT_TEXT_FONT_SIZE };

            std::string msg { WSDL_DEFAULT_TEXT_MSG };
            SDL_Color color { WSDL_DEFAULT_TEXT_COLOR };

            bool modified { WSDL_DEFAULT_TEXT_MODIFIED };
            SDL_Rect rect { WSDL_DEFAULT_TEXT_LOCATION, WSDL_DEFAULT_TEXT_SIZE };
            
            bool make();
            void moveAttributes(Text&&) noexcept;
            void copyAttributes(const Text&);
    };
}

