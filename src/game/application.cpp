#include "../../include/game/application.h"

void start(const std::string& settings_profile) {
    srand(time(NULL));

    Settings settings;
    bool success;
    std::tie(settings, success) = loadSettings(settings_profile);
    if (!success) {
        std::cout << "Invalid profile. Please provide a proper one.\n";
        return;
    }

    wsdl::SDL_Initialize dummy_init_object;
    SDL_ShowCursor(SDL_DISABLE);
    wsdl::Window window ("Ball Game", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720 }, SDL_WINDOW_SHOWN);
    window.spawn();
    if (SDL_SetWindowFullscreen(window.get(), settings.window_mode)) {
        std::cout << SDL_GetError() << '\n';
    }
    // SDL_RENDERER_ACCELERATED may cause problems
    wsdl::Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (SDL_RenderSetLogicalSize(renderer.get(), 1280, 720)) {
        std::cout << SDL_GetError() << '\n';
    }

    // a level shall have 20 (0 - 19) blocks horizintally and 16 (0 - 15) vertically
    unsigned int paddles; // how many times you can lose the ball
    unsigned int score;
    bool exit_to_menu = false; 
    const std::string assets_dir = "../assets/" + settings.assets + '/';
    while(1) {
        if (menu_screen(window, renderer, assets_dir)) {
            break;
        }
        paddles = 3;
        score = 0;
        for (const auto& board : settings.boards) {
            // there's no such thing as "too many parameters"... apparently...
            run(window, renderer, assets_dir, board, settings.bg_color, paddles, score, exit_to_menu);
            if (exit_to_menu) {
                break;
            }
            if (paddles == 0) {
                break;
            }
        }
        score_screen(window, renderer, assets_dir, score);
    }
}

std::pair<Input, bool> listen() {
    Input input;
    bool exit_flag = false;
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:
                exit_flag = true;
                break;
            case SDL_KEYDOWN:
                listenKeyDown(ev.key, input);
                break;
            case SDL_KEYUP:
                listenKeyUp(ev.key, input);
                break;
            case SDL_MOUSEBUTTONUP:
                input.any_mouse_button = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                input.any_mouse_button = false;
            default:
                break;
        }
    }
    SDL_GetMouseState(&input.mouse_x, &input.mouse_y);
    return { input, exit_flag };
}

void listenKeyUp(SDL_KeyboardEvent& ev, Input& input) {
    if (ev.repeat) {
        return;
    }
    if (ev.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        input.esc = true;
    }
    if (ev.keysym.scancode == SDL_SCANCODE_SPACE) {
       input.space_bar = true;
    }
}

void listenKeyDown(SDL_KeyboardEvent& ev, Input& input) {
    if (ev.repeat) {
        return;
    }
    if (ev.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        input.esc = false;
    }
    if (ev.keysym.scancode == SDL_SCANCODE_SPACE) {
        input.space_bar = false;
    }
}

std::pair<Settings, bool> loadSettings(const std::string& settings_profile) { // make this function simpler, break it apart
    Settings settings;
    std::ifstream settings_file("../settings/" + settings_profile);
    if (!settings_file.is_open()) {
        return std::make_pair(settings, 0);
    }
    std::string line;
    while(getline(settings_file, line)) {
        std::string option, value;
        std::tie(option, value) = readLine(line);
        // choose option
        if (option == "assets") {
            settings.assets = value;
        }
        if (option == "boards") {
            std::vector<std::string> board_files = splitString(value, ';');
            for (std::string& i : board_files) {
                std::ifstream board_file("../boards/" + i);
                if (!board_file) {
                    return std::make_pair(settings, 0);
                }
                settings.boards.push_back(readBoard(board_file));
                board_file.close();
            }
        }
        if (option == "bgColor") {
            std::vector<std::string> rgb = splitString(value, ';');
            try {
                settings.bg_color.r = std::stoi(rgb[0]);
                settings.bg_color.g = std::stoi(rgb[1]);
                settings.bg_color.b = std::stoi(rgb[2]);
            } catch (const std::exception& e) {
                settings.bg_color = { 0, 0, 0 };
                std::cout << "[Problematic settings profile] " << settings_profile << " -> bgColor (invalid input or out of range). Using default color instead.\n";
            } 
        }
        if (option == "windowMode") {
            if (value == "full") {
                settings.window_mode = SDL_WINDOW_FULLSCREEN;
            } else if (value == "winfull") {
                settings.window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
            } else {
                settings.window_mode = 0;
            }
        }
    }
    settings_file.close();
    return std::make_pair(settings, 1);
}

std::vector<std::string> splitString(std::string str, const char& delimiter) {
    std::vector<std::string> output;
    std::string temp;
    for (char& i : str) {
        if (i == delimiter) {
            output.push_back(temp);
            temp.clear();
            continue;
        }
        temp.push_back(i);
    }
    return output;
}

std::pair<std::string, std::string> readLine(std::string line) {
    std::string *which, option {}, value {};
    if (line[0] == '#') {
        return std::make_pair((std::string){}, (std::string){});
    }
    which = &option;
    for (char& i : line) {
        if (((int) i >= 48 && (int) i <= 57)  ||
            ((int) i >= 65 && (int) i <= 90)  || 
            ((int) i >= 97 && (int) i <= 122) || 
            i == ';') {
            which->push_back(i);
        } else if (i == ':') {
            which = &value;
        }
    }
    return std::make_pair(option, value);
}

Board readBoard(std::ifstream& board_file) {
    Board board;
    BLine bline;
    std::string fline; // file line
    while (getline(board_file, fline)) {
        for (char& j : fline) {
            bline.push_back(j);
        }
        board.push_back(bline);
        bline.clear();
    }
    return board;
}

bool probablyTrue(const unsigned int& probability) {
    return (rand() % 100) < probability;
}

int randomNumber(const int& a, const int& b) {
    return rand() % b + a;
}

std::string getRandomMessage(const std::string& assets_dir) {
    std::ifstream messages_file(assets_dir + "messages.txt");
    if (!messages_file.is_open()) {
        return {};
    }
    std::vector<std::string> vec_of_strings;
    std::string str;
    while(getline(messages_file, str)) {
        vec_of_strings.push_back(std::move(str));
    }
    return vec_of_strings[randomNumber(0, vec_of_strings.size() - 1)];
}

void run(const wsdl::Window& window, const wsdl::Renderer& renderer, const std::string& assets_dir, const Board& board, const SDL_Color& bg_color, unsigned int& paddles, unsigned int& score, bool& exit_to_menu) {
    Input input; // recorded input
    Control control; // control flow

    //Paddle paddle = Paddle::defaultPaddle(renderer, assets_dir);
    Paddle paddle(renderer, assets_dir);
    // the paddle shall be 20px tall
    
    std::unique_ptr<PowerupManager> powerupManager { nullptr }; // this type cannot be complete here so I used a pointer instead...
    BlockManager blockManager(renderer, assets_dir, board, score, powerupManager);
    // block size: 64x30 (1280x720), the texture shall be scaled accordingly in other resolutions
    BallManager ballManager(renderer, assets_dir, paddle, blockManager);
    // ball's base speed (default = 4), factor (see macros)
    // the ball shall be 15x15 (normal)
    powerupManager.reset(new PowerupManager(renderer, assets_dir, score, paddle, ballManager, blockManager)); // ... and finally make it here. Not the best thing but it seems to be working alright...
    // obviously, powerManager should only be used after this line (including blockManager's constructor)... it's very dangerous

    wsdl::Text paddles_left(renderer, DEFAULT_FONT, 30);
    paddles_left = std::to_string(paddles);
    paddles_left.setColor({ 222, 93, 93 });
    paddles_left.setLocation({ window.getRect().w - 30, 10 });
    TTF_SetFontStyle(paddles_left.get(), TTF_STYLE_BOLD);

    wsdl::Text score_text(renderer, DEFAULT_FONT, 30);
    score_text = std::to_string(score);
    score_text.setColor({ 222, 93, 93 });
    score_text.setLocation({ 10, 10 });
    TTF_SetFontStyle(score_text.get(), TTF_STYLE_BOLD);

    do {
        SDL_SetRenderDrawColor(renderer.get(), bg_color.r, bg_color.g, bg_color.b, 255);
        SDL_RenderClear(renderer.get());

        std::tie(input, exit_to_menu) = listen(); // listening for input 

        if (input.esc && pause(window, renderer, assets_dir)) {
            exit_to_menu = true;
            return;
        }

        if (control.ready && input.any_mouse_button) {
            control.ready = false;
        }
        
        ballManager.logic(control.darkest_pit_of_hell, control.ready); // might change darkest_pit_of_hell to true (when all balls get lost), but merely monitors ready
        powerupManager->logic(control.darkest_pit_of_hell); // might change darkest_pit_of_hell to true (when drop 5 is catched)
        if (control.darkest_pit_of_hell) {
            paddles_left = std::to_string(--paddles);
            ballManager.reset();
            powerupManager->clear();
            paddle.reset();
            control.ready = true;
            control.darkest_pit_of_hell = false; // reset
        }
        if (paddles == 0 || blockManager.isEmpty()) {
            control.loop_flag = false;
            break;
        }
        paddle.logic(input); // merely monitors input
        score_text = std::to_string(score);
        if (exit_to_menu) {
            return;
        }

        // output
        blockManager.blit();
        paddle.blit();
        ballManager.blit();
        paddles_left.print();
        score_text.print();
        powerupManager->blit();

        // printing the end result
        SDL_RenderPresent(renderer.get());
        SDL_Delay(16); // ~ 60 FPS
    } while(control.loop_flag);
}

bool pause(const wsdl::Window& window, const wsdl::Renderer& renderer, const std::string& assets_dir) {
    wsdl::Text message(renderer, DEFAULT_FONT, 30);
    message = "Press ESC again to exit to main menu or SPACE to continue...";
    message.setColor({ 200, 200, 255 });
    message.setLocation({ 50, window.getRect().h / 2 - 30});

    BackgroundPattern bg_pattern(window, renderer, assets_dir + "sky_pattern.png");
    do {
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(renderer.get());

        auto [input, exit_to_menu] = listen();
        if (input.esc || exit_to_menu) {
            return true;
        } else if (input.space_bar) {
            return false;
        }

        bg_pattern.blit();
        message.print();

        SDL_RenderPresent(renderer.get());
        SDL_Delay(16); // ~ 60 FPS
    } while(1);
}

bool menu_screen(const wsdl::Window& window, const wsdl::Renderer& renderer, const std::string& assets_dir) {
    enum class Choice {
        do_nothing,
        play,
        exit
    };

    Choice choice = Choice::do_nothing;

    wsdl::Text title(renderer, DEFAULT_FONT, 80);
    title = "Ball Game";
    title.setColor({ 200, 200, 255 });
    title.setLocation({ 50, 50 });
    TTF_SetFontStyle(title.get(), TTF_STYLE_ITALIC);

    wsdl::Text title_shadow(title);
    title_shadow.setColor({ 27, 0, 100 });
    title_shadow.setLocation({ 55, 55 });
    TTF_SetFontStyle(title_shadow.get(), TTF_STYLE_ITALIC);

    wsdl::Text subtitle(renderer, DEFAULT_FONT, 30);
    subtitle = getRandomMessage(assets_dir);
    subtitle.setColor({ 200, 200, 255 });
    subtitle.setLocation({ 50, 150 });
    TTF_SetFontStyle(title_shadow.get(), TTF_STYLE_ITALIC);

    wsdl::Sprite mouse_cursor(renderer, assets_dir + "mouse_cursor.png");
    Button play_button(renderer, assets_dir + "play_button.png");
    play_button.setLocation({ 
        50, 
        window.getRect().h / 2 - play_button.getRect().h / 2 
    });
    Button exit_button(renderer, assets_dir + "exit_button.png");
    exit_button.setLocation({
        50,
        window.getRect().h - play_button.getRect().h - 50
    });

    BackgroundPattern bg_pattern(window, renderer, assets_dir + "sky_pattern.png");

    do {
        SDL_SetRenderDrawColor(renderer.get(), 36, 31, 49, 255);
        SDL_RenderClear(renderer.get());

        auto [input, exit_entirely] = listen();
        if (exit_entirely) {
            return true;
        }

        mouse_cursor.setLocation({ input.mouse_x, input.mouse_y });
        play_button.logic(input, [&choice](Button& button){
            choice = Choice::play;
        });
        exit_button.logic(input, [&choice](Button& button) {
            choice = Choice::exit;
        });

        switch(choice) {
            case Choice::play:
                return false;
            case Choice::exit:
                return true;
            default:
                break;
        }

        bg_pattern.blit();
        title_shadow.print();
        title.print();
        subtitle.print();
        play_button.blit();
        exit_button.blit();
        mouse_cursor.blit();

        SDL_RenderPresent(renderer.get());
        SDL_Delay(16); // ~ 60 FPS
    } while(1);
}

void score_screen(const wsdl::Window& window, const wsdl::Renderer& renderer, const std::string& assets_dir, unsigned int& score) {
    wsdl::Text score_text(renderer, DEFAULT_FONT, 30);
    score_text = "Your score is: " + std::to_string(score);
    score_text.setColor({ 200, 200, 255 });
    score_text.setLocation(
        { 
            50, 
            window.getRect().h / 2 - 15 
        }
    );
    TTF_SetFontStyle(score_text.get(), TTF_STYLE_BOLD);

    wsdl::Text subtext(renderer, DEFAULT_FONT, 30);
    subtext = "Press SPACE to continue...";
    subtext.setColor({ 200, 200, 255 });
    subtext.setLocation(
        { 
            50, 
            window.getRect().h - 50 
        }
    );

    BackgroundPattern bg_pattern(window, renderer, assets_dir + "sky_pattern.png");

    do {
        SDL_SetRenderDrawColor(renderer.get(), 36, 31, 49, 255);
        SDL_RenderClear(renderer.get());

        auto [input, exit_flag] = listen();
        if (exit_flag || input.space_bar) {
            return;
        }

        bg_pattern.blit();
        score_text.print();
        subtext.print();

        SDL_RenderPresent(renderer.get());
        SDL_Delay(16); // ~ 60 FPS
    } while(1);
}
