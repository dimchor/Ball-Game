#pragma once

#include "../wsdl/wsdl_sprite.h"
#include "../game/application.h"

struct Input;

class Button : public wsdl::Sprite {
    public:
        Button(const wsdl::Renderer&, const std::string&);
        void logic(const Input&, std::function<void(Button&)>);
    private: 

};
