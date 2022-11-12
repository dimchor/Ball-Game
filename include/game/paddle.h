#pragma once

#include "application.h"
#include "../wsdl/wsdl_sprite.h"

#define SMALL 1
#define MEDIUM 2
#define LARGE 3

struct Input;

class Paddle : public wsdl::Sprite {
    public:
        Paddle(const wsdl::Renderer&, std::string);
        void logic(const Input&);
        void enlarge();
        void contract();
        void reset();
    private:
        std::string assets_dir;
        unsigned int size = MEDIUM;
};
