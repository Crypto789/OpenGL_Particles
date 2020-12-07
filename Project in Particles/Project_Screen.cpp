#include <iostream>
#include <SDL.h>
#include "Project_Screen.h"



 Project_Screen::Project_Screen():
     mWindow(NULL), mrenderer(NULL), mtexture(NULL), mbuffer1(NULL), mbuffer2(NULL) {}

bool Project_Screen::init() 
{ 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }

    mWindow = SDL_CreateWindow("Particle Project",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wScreen, hScreen, SDL_WINDOW_SHOWN);

    if (mWindow == NULL)
    {
        SDL_Quit();
        return false;
    }

    /*THis will will render and sync screen
    this prevents flinkering on screnn when is being refresh*/
    mrenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    mtexture = SDL_CreateTexture(mrenderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STATIC, wScreen, hScreen);

    if (mrenderer == NULL)
    {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    if (mtexture == NULL)
    {
        SDL_DestroyRenderer(mrenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return false;
    }

    mbuffer1 = new Uint32[wScreen * hScreen];
    mbuffer2 = new Uint32[wScreen * hScreen];

    memset(mbuffer1, 0, wScreen * hScreen * sizeof(Uint32));
    memset(mbuffer2, 0, wScreen * hScreen * sizeof(Uint32));

    //Creates a single pixel
   // buffer[30000] = 0xFFFFFFFF;

    /*this assigns pixels in window and gives color*/
    /*for (int i = 0; i < wScreen * hScreen; i++)
    {
        mbuffer[i] = 0xFF0000FF;
    }*/

    return true; 
}
void Project_Screen::boxBLur() 
{
    //swapping buffers to draw buffer one.
    Uint32* temp = mbuffer1;;
    mbuffer1 = mbuffer2;
    mbuffer2 = temp;

    for (int y = 0; y < hScreen; y++)
    {
        for (int x = 0; x < wScreen; x++) 
        {
            int redTotal = 0;
            int greenTotal = 0;
            int BLueTotal = 0;

            for (int row =- 1; row <= 1; row++) 
            {
                for (int col =- 1; col <= 1; col++)
                {
                    int currentX = x + col;
                    int currentY = y + row;

                    if (currentX >= 0 && currentX < wScreen && currentY >= 0 && currentY < hScreen) 
                    {
                        Uint32 color = mbuffer2[currentY * wScreen + currentX];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        BLueTotal += blue;
                    }
                }
            }
            Uint8 red = redTotal / 9;
            Uint8 green = greenTotal / 9;
            Uint8 blue = BLueTotal / 9;
            setScreenpixels(x, y, red, green, blue);
        }
    }
}

/*void Project_Screen::Clear()
{
    memset(mbuffer1, 0, wScreen * hScreen * sizeof(Uint32));
    memset(mbuffer2, 0, wScreen * hScreen * sizeof(Uint32));
}*/

void Project_Screen::setScreenpixels(int x, int y, Uint8 red, Uint8 green, Uint8 blue) 
{
    if (x < 0 || x >= wScreen || y < 0 || y >= hScreen) 
    {
        return;
    }
    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    mbuffer1[(y * wScreen) + x] = color;
}

void Project_Screen::Screen_update() 
{
    SDL_UpdateTexture(mtexture, NULL, mbuffer1, wScreen * sizeof(Uint32));
    SDL_RenderClear(mrenderer);
    SDL_RenderCopy(mrenderer, mtexture, NULL, NULL);
    SDL_RenderPresent(mrenderer);
}

bool Project_Screen::processEvent() 
{ 
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true; 
}

void Project_Screen::close() 
{
    delete[] mbuffer1;
    delete[] mbuffer2;
    SDL_DestroyRenderer(mrenderer);
    SDL_DestroyTexture(mtexture);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

