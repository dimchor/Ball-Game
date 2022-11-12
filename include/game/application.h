#pragma once

#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <time.h>

#include "../wsdl/wsdl.h"
#include "../wsdl/wsdl_window.h"
#include "../wsdl/wsdl_renderer.h"
#include "../wsdl/wsdl_sprite.h"
#include "../wsdl/wsdl_text.h"

using BLine = std::vector<char>; // board line
using Board = std::vector<BLine>; // board itself

#include "paddle.h"
#include "block.h"
#include "ball.h"
#include "powerup.h"
#include "blockmanager.h"
#include "ballmanager.h"
#include "powerupmanager.h"

#include "../interface/button.h"

#include "bg_pattern.h"

#define BLOCK_W 64
#define BLOCK_H 30

#define SLOW 1.0f
#define NORMAL 1.5f
#define FAST 2.0f

#define DROP_PROBABILITY 20
#define DROP_NUMBER 8

#define DEFAULT_FONT "../fonts/shared.ttf"

#define BLOCK_POINTS 10
#define POWERUP_POINTS 100

// key input
struct Input {
    int mouse_x;
    int mouse_y;
    bool space_bar = false;
    bool esc = false;
    bool any_mouse_button = false;
};

struct Control {
    bool ready = true;
    bool loop_flag = true;
    bool darkest_pit_of_hell = false;
};

struct Settings {
    std::string assets;
    std::vector<Board> boards;
    SDL_Color bg_color { 0, 0, 0 };
    Uint32 window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
};

void start(const std::string&);
bool menu_screen(const wsdl::Window&, const wsdl::Renderer&, const std::string&);
void run(const wsdl::Window&, const wsdl::Renderer&, const std::string&, const Board&, const SDL_Color&, unsigned int&, unsigned int&, bool&);
std::pair<Input, bool> listen();
void listenKeyUp(SDL_KeyboardEvent&,Input&);
void listenKeyDown(SDL_KeyboardEvent&,Input&);
std::pair<Settings, bool> loadSettings(const std::string&);
std::vector<std::string> splitString(std::string, const char&);
std::pair<std::string, std::string> readLine(std::string);
Board readBoard(std::ifstream&);
bool probablyTrue(const unsigned int&);
int randomNumber(const int&, const int&);
bool pause(const wsdl::Window&, const wsdl::Renderer&, const std::string&);
void score_screen(const wsdl::Window&, const wsdl::Renderer&, const std::string&, unsigned int&);
std::string getRandomMessage(const std::string&);