#pragma once

#include <vector>

#include "../wsdl/wsdl.h"
#include "../wsdl/wsdl_window.h"
#include "../wsdl/wsdl_renderer.h"
#include "../wsdl/wsdl_sprite.h"

class BackgroundPattern {
    public:
        BackgroundPattern(const wsdl::Window&, const wsdl::Renderer&, const std::string&);
        void blit() const;
    private:
        const wsdl::Window* window { nullptr };
        const wsdl::Renderer* renderer { nullptr };

        std::vector<wsdl::Sprite> sprites;
};
