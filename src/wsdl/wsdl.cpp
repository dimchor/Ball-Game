#include "../../include/wsdl/wsdl.h"

// a simple logger, nothing special
void wsdl::Log::Error(std::string msg) {
    std::cout << "[ERROR] " << msg << '\n';
}

void wsdl::Log::Info(std::string msg) {
    std::cout << " [INFO] " << msg << '\n';
}

std::string wsdl::Log::getDetails() {
    std::string details = SDL_GetError();
    return " [SDL: " + details + "] ";
}

// an simple destructor struct that's used for freeing memory
// the struct is passed into a smart pointer (in this case, a unique_ptr)
void wsdl::SDL_Delete::operator()(SDL_Window* p) {
    if (p) {
        SDL_DestroyWindow(p);
    }
}

void wsdl::SDL_Delete::operator()(SDL_Surface* p) {
    if (p) {
        SDL_FreeSurface(p);
    }
}

void wsdl::SDL_Delete::operator()(SDL_Renderer* p) {
    if (p) {
        SDL_DestroyRenderer(p);
    }
}

void wsdl::SDL_Delete::operator()(SDL_Texture* p) {
    if (p) {
        //wsdl::Log::Info("Texture Gone!");
        SDL_DestroyTexture(p);
    }
}

void wsdl::SDL_Delete::operator()(TTF_Font* p) {
    if (p) {
        TTF_CloseFont(p);
    }
}

// a simple function that checks if a pointer is valid or not
bool wsdl::isValid(const void* ptr) {
    if (ptr) {
        //Log::Error("Pointer dereference error occured." + Log::getDetails());
        return true;
    }
    return false;
}

wsdl::Vector2::Vector2(int x, int y) {
    this->x = std::move(x);
    this->y = std::move(y);
}

void wsdl::Vector2::reverseX() {
    x = -x;
}

void wsdl::Vector2::reverseY() {
    y = -y;
}

wsdl::SDL_Initialize::SDL_Initialize() {
    Log::Info("Staring...");
    Log::Info("Initializing video...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Log::Error("Unable to initialize video." + wsdl::Log::getDetails());
    }
    if (TTF_Init() < 0) {
        Log::Error("Unable to initialize fonts." + wsdl::Log::getDetails());
    }
}

wsdl::SDL_Initialize::~SDL_Initialize() {
    Log::Info("Exiting...");
    TTF_Quit();
    SDL_Quit();
}

