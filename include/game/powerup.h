#pragma once

#include "../wsdl/wsdl_sprite.h"

class Powerup : public wsdl::Sprite {
    private:
        wsdl::Vector2 vector;
        unsigned int code;
    public:
        Powerup(const wsdl::Renderer&, const std::string&);
        Powerup(const wsdl::Renderer&, const std::string&, const wsdl::Vector2&, const wsdl::Vector2&, const unsigned int&);

        void logic();

        wsdl::Vector2& setVector();
        void setVector(const wsdl::Vector2&);
        const wsdl::Vector2& getVector() const;
        const unsigned int& getCode() const;
};
