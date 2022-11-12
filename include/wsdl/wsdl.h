#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include "SDL2/SDL.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

namespace wsdl {
    namespace Log {
        void Error(std::string);
        void Info(std::string);
        std::string getDetails();
    }

    struct SDL_Delete {
        void operator() (SDL_Window*);
        void operator() (SDL_Surface*);
        void operator() (SDL_Renderer*);
        void operator() (SDL_Texture*);
        void operator() (TTF_Font*);
    };

    using surface_ptr = std::unique_ptr<SDL_Surface, SDL_Delete>;
    using renderer_ptr = std::unique_ptr<SDL_Renderer, SDL_Delete>;
    using texture_ptr = std::unique_ptr<SDL_Texture, SDL_Delete>;
    using window_ptr = std::unique_ptr<SDL_Window, SDL_Delete>;
    using font_ptr = std::unique_ptr<TTF_Font, SDL_Delete>;

    bool isValid(const void*);
    
    struct Vector2 : public SDL_Point {
        Vector2() = default;
        Vector2(int x, int y);

        void reverseX();
        void reverseY();
    };
    
    struct SDL_Initialize {
        SDL_Initialize();

        SDL_Initialize(SDL_Initialize&&) = delete;
        SDL_Initialize& operator=(SDL_Initialize&&) = delete;
        SDL_Initialize(const SDL_Initialize&) = delete;
        SDL_Initialize& operator=(const SDL_Initialize&) = delete;

        ~SDL_Initialize();
    };

}
