#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "JEngine.h"

JEngine* j;
int main(int argc, char* args[])
{
	
	j = new JEngine(); 
	j->setInputFrameIndependant(true);
	j->init("Window",640,480,60);
	j->setMaxFrameRate(144);

	bool quit = 0;
	JRenderer * renderer = new JRenderer(200, 200, 640, 480);
	j->addElement(renderer);
	Rect * rect = new Rect(100, 100, 50, 30,255,0,255,120);
	Rect * rect2 = new Rect(100, 200, 50, 30, 255, 0, 255, 120);
	j->addElement(rect);
	renderer->addElement(rect);
	renderer->addElement(rect2);
	for (int i = 0;i < 480;i++) {
		renderer->addElement(new Rect(i % 30*64, i / 30*64, 35, 35, 255, 0, 0, 250));
	}
	while (!quit) {
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;


		}
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_D))
		{
			rect->moveBy(200, 0);

		}
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_D))
		{
			renderer->getImageManager()->removeAndDeleteAllElements();

		}
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_X))
		{
			for (int i = 0;i < 500;i++) {
				renderer->addElement(new Rect(0, 0, 200, 200, 55, 5, 55, 55));
			}

		}
		rect2->moveBy(200, 0);
		j->refreshScreen();
	}
	return 0;
}
