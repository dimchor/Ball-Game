# Ball Game
This is merely a breakout clone. I got heavily inspired by a game call DX-Ball, which is another breakout clone. As a matter of fact, many of DX-Ball's core features are in this game too (please don't sue me 😅) except that this one is worse in every possible way. 
# Compilation
On Ubuntu 20.04, you'll need the following packages: `g++ libsdl2-dev libsdl-image1.2-dev libsdl2-image-dev libsdl2-ttf-dev`. All of which can be obtained using `apt`.

After installing the aforementioned packages, clone this repository locally on your machine and change to its directory. After which, compile using `g++ -o build/run src/game/*.cpp src/interface/*.cpp src/wsdl/*.cpp -std=c++17 -lSDL2 -lSDL2_image -lSDL2_ttf`. If you navigate to the `build` folder, should see a file named `run`. Execute it with no arguments to launch the game using default settings.
# Settings
You can customize many aspects of the game. In particular, all of the game's (ugly) assets can be swapped with (perhaps better-looking) custom ones, provided that the new files have the exact same size and name as the original ones. The background color can be changed too. You can also make unique boards, if you get bored of the included ones.
## Boards
A board is a text file with no extension. It shall have up to 16 lines and each line shall have up to 20 characters. The following characters are allowed to be in this file:
 - `0`: meaning "air" or "nothing".
 - `1`-`3`: meaning classic block. The number denotes how many hits it takes to break it.
 - `T`: meaning TNT block.
## Assets
It is recommended that you make a new folder with your custom assets under the `assets/` directory and not directly replace the default assets (`assets/default/` directory).
## Settings file (profile)
Make a new file under the `settings/` directory. In it, type the following *at minimum*: 
```
assets: <name of the assets folder (ex. default)>
boards: <name of the boards, separated by ';' and also adding another one at the end (ex. triangle; square;)>
```
The following options are also available:
 - `bgColor: <red>; <green>; <blue>;`: which changes the default background color in each level.
 - `windowMode: <0 or full or winfull>`: which overrides the default window option. `winfull` (windowed fullscreen) is used by default.
Have a look at the existing profiles, if you aren't too sure about your custom one.
