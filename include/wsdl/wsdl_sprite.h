#pragma once

#include "wsdl.h"
#include "wsdl_object.h"
#include "wsdl_renderer.h"

#define WSDL_DEFAULT_SPRITE_LOCATION 0, 0
#define WSDL_DEFAULT_SPRITE_SIZE 0, 0

namespace wsdl {
    class Sprite : public WSDL_Object<SDL_Texture> {
        public:
            Sprite() = default;
            Sprite(const Renderer&, const std::string&);
            Sprite(Sprite&&) noexcept;
            Sprite& operator=(Sprite&&) noexcept;
            Sprite(const Sprite&);
            Sprite& operator=(const Sprite&);

            const Renderer& getRenderer() const;
            const std::string& getFilePath() const;
            const int& getX() const;
            const int& getY() const;
            const int& getW() const;
            const int& getH() const;
            const SDL_Rect& getRect() const;
            const wsdl::Vector2 getLocation() const;
            void setX(const int&);
            void setY(const int&);
            void setRect(const SDL_Rect&);
            void setLocation(const Vector2&);

            void blit() const;

            bool reset(const Renderer&, const std::string&);
            bool resetTexture(const std::string&);
        private:
            const Renderer* renderer { nullptr };
            std::string file_path {};
            SDL_Rect rect { WSDL_DEFAULT_SPRITE_LOCATION, WSDL_DEFAULT_SPRITE_SIZE };
            
            bool make();
            void moveAttributes(Sprite&&) noexcept;
            void copyAttributes(const Sprite&);
    };
}

