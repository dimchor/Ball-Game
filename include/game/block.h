#pragma once

#include "../wsdl/wsdl_sprite.h"
#include "application.h"

#define TYPE_CLASSIC 0
#define TYPE_TNT 1

class Block : public wsdl::Sprite {
    public:
        Block(const wsdl::Renderer&, std::string, std::string, wsdl::Vector2, unsigned int, unsigned int);

        const int& getGridX() const;
        const int& getGridY() const;
        const wsdl::Vector2& getGridLocation() const;
        const unsigned int& getDropCode() const;
        const unsigned int& getHitsLeft() const;
        const unsigned int& getType() const;

        void hit();
    private:
        std::string assets_dir;
        wsdl::Vector2 grid_location;
        unsigned int drop = 0;
        unsigned int hits_left = 1;
        unsigned int type = TYPE_CLASSIC;
};

