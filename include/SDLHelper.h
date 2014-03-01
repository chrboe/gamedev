#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#ifndef SDLHELPER_H
#define SDLHELPER_H

using namespace std;

class SDLHelper
{
    public:
        static bool init(int window_width, int window_heigth);
        static void events();
        static SDL_Renderer* renderer;
        static SDL_Texture* loadTextureFromFile(string path);
        static SDL_Window* window;
        static void free();
        static int WINDOW_HEIGHT;
        static int WINDOW_WIDTH;
    private:
        SDLHelper();
        ~SDLHelper();


        static bool quit;
};

#endif // SDLHELPER_H
