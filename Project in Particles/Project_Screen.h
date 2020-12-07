


#include <SDL.h>


class Project_Screen
{
public:
	const static int wScreen = 1920;
	const static int hScreen = 1080;
private:
	SDL_Window *mWindow;
	SDL_Renderer *mrenderer;
	SDL_Texture *mtexture;
	Uint32 *mbuffer1;
	Uint32 *mbuffer2;
public:
	Project_Screen();
	void Screen_update();
	bool init();
	void setScreenpixels(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvent();
	void close();
	//void Clear();
	void boxBLur();
};

