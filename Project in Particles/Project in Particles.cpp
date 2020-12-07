// Project in Particles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include "Project_Screen.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"


int main(int argc, char* args[])
{
    srand(time(NULL));

    Project_Screen screen;

    if (screen.init() == false) 
    {
        std::cout << "Error on SDL Initial."<< std::endl;
    }
    Swarm swarm;

    while (true) 
    {
        int elapsed = SDL_GetTicks();

        //screen.Clear();
        swarm.ParticlesUpdate(elapsed);
        unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.001) * 128));
       // unsigned char red = (unsigned char)((1 + sin(elapsed * 0.001) * 255));
        //unsigned char green = (unsigned char)((1 + sin(elapsed * 0.001) * 255));

        // prints pixels on screen scattered around
        const Particles* const pParticles = swarm.get_particles();
        for (int i = 0; i < Swarm::mPARTICLES; i++) 
        {
            Particles particles = pParticles[i];

            int x = (particles.mX + 1) * Project_Screen::wScreen / 2;
            //int y = (particles.mY + 1) * Project_Screen::hScreen / 2;
            int y = particles.mY * Project_Screen::wScreen / 2 + Project_Screen::hScreen / 2;

            screen.setScreenpixels(x, y, blue, 255, 255);
        }

        screen.boxBLur();

        //this will draw particles and Update
        /*for (int y = 0; y < Project_Screen::hScreen; y++)
        {
            for (int x = 0; x < Project_Screen::wScreen; x++)
            {
                screen.setScreenpixels(x, y, skyBlue, 255, 255);
            }
        }*/
        //screen.setScreenpixels(400, 300, 255, 255, 255);

        //this will draw on the screen
        screen.Screen_update();

        //this will check for events and messages
        if (screen.processEvent() == false) 
        {
            break;
        }
    }
    screen.close();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
