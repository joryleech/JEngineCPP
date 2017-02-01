#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "j.h"
#include "JEngine.h"
double scale =4;
void moveCamera(int pos)
{
	int camspeed=4;
	if (pos == 0) {
		j->moveCameraBy(((0 * scale) - j->getCameraX())*camspeed, 0);
	}
	else if (pos == 1)
	{ 
		j->moveCameraBy(((520 * scale) - j->getCameraX())*camspeed, 0);
	}
	else if (pos == 2) {
		j->moveCameraBy(((950 * scale) - j->getCameraX())*camspeed, 0);
	}
}

void gameplay() {
	int bossSpeed = 5 * scale;
	int bossMax = 100;
	int camX=0;int camY=0;
	int pos = 2;
	bool buttonPressed1 = false; //left
	bool buttonPressed2 = false; //right
	bool done = false;
	bool working = false;
	Image* boss = new Image("boss.png", bossMax*scale, 0);
	Image* screenFront = new Image("screenFront.png", 0, 0);
	Image* backgroundAndDesk= new Image("background.png", 0, 0);
	Image* deskButtonUp = new Image("buttonUp.png", 0, 0);
	Image* deskButtonDown = new Image("buttonDown.png", 0, 0);
	Image* deskButton = new Image(deskButtonUp, 1330 * scale, 246 * scale);
	Image* buttonUp= new Image("sideButton.png", 0, 0);
	Image* buttonDown = new Image("sideButtonDown.png", 0, 0);
	Image* button1 = new Image(buttonUp, 0, 0);
	Image* button2 = new Image(buttonUp, 0, 0);
	Image* cursor = new Image("cursor.png", 0, 0);
	Image* work = new Image("work.png", 1013*scale, 18*scale);
	//work->hide();
	work->setScale(scale);
	button1->setScale(scale);
	button2->setScale(scale);
	boss->setScale(scale);
	button2->setFlip(SDL_FLIP_HORIZONTAL);
	JInput* in=j->getJInput();
	backgroundAndDesk->setScale(scale);
	screenFront->setScale(scale);
	work->hide();
	deskButton->setScale(scale);

	j->addElement(boss);
	j->addElement(backgroundAndDesk);
	j->addElement(work);
	j->addElement(screenFront);
	j->addElement(deskButton);
	
	j->addElement(button1);
	j->addElement(button2);
	j->addElement(cursor);

	while (!done) {
		moveCamera(pos);
		if (in->isKeyDown(SDL_SCANCODE_ESCAPE)) {
			done = true;
		}
		if (cursor->isColliding(button2) && in->isMouseDown() ) {
			button2->setImage(buttonDown);
			if (pos < 2 && buttonPressed1 == false) {
				pos++;
				buttonPressed1 = true;
			}
		}
		else {
			buttonPressed1 = false;
			button2->setImage(buttonUp);
		}
		if (cursor->isColliding(button1) && in->isMouseDown()) {
			button1->setImage(buttonDown);
			if (pos > 0 && !buttonPressed2) {
				pos--;
				buttonPressed2 = true;
			}
		}
		else {
			buttonPressed2 = false;
			button1->setImage(buttonUp);
		}
		//deskButton
		if (cursor->isColliding(deskButton) && in->isMouseDown())
		{
			work->show();
			working = true;
			deskButton->setImage(deskButtonDown);
		}
		else { work->hide();working = false; deskButton->setImage(deskButtonUp); }
		if (working) {
			if (boss->getX() < bossMax*scale) {
				boss->moveBy(bossSpeed * 4,0);
			}
		}
		else { boss->moveBy(-bossSpeed, 0); }


		if (in->isKeyDown(SDL_SCANCODE_1))
			pos = 0;
		if (in->isKeyDown(SDL_SCANCODE_2))
			pos = 1;
		if (in->isKeyDown(SDL_SCANCODE_3))
			pos = 2;
		cursor->moveTo((int)j->getCameraX() + in->getMouseXPos(), (int)j->getCameraY() + in->getMouseYPos());
		button1->moveTo(((int)j->getCameraX() + (5*scale)), (119 * scale));
		button2->moveTo(((int)j->getCameraX() + (443*scale)), (119 * scale));
		
		j->refreshScreen();
		
	}
}

int main(int argc, char* args[])
{
	
	//JEngine* j = new JEngine();
	j = new JEngine(); 
	j->setInputFrameIndependant(true);
	j->init("Window",1920,1080,60);
	j->setMaxFrameRate(60);
	j->setWindowFullScreen();

	gameplay();
	return 0;
}

void gameplayTest1() {
	bool quit = false;
	double time = 0;
	int frame;

	Image* cursor = new Image("cursor.png", 0, 0);
	Image* r = new Image("7.bmp", 2, 390);
	Image* walk1 = new Image("walk2.png", 0, 0);
	Image* idle = new Image("5.png", 0, 0);
	Image* desk = new Image("desk.png", 0, 0);
	Rect* mal = new Rect(20, 20, 10, 10, 255, 0, 0, 255);
	cursor->setScale(2);

	//desk->setScale(2);
	r->setScale(2);


	j->addElement(desk);

	j->addElement(cursor);	j->addElement(mal);	j->addElement(r);
	int speed = 61;
	double jump = 0;
	double frame2 = 0;
	while (!quit) {
		frame2 += j->getTimeStep() / 1000.0f;


		time += 60 * (j->getTimeStep()) / 1000.0f;
		frame = (int)(time / 5) % 7;
		//r->setBlit((frame%3)*32,((frame)>2)*50,32,50);


		cursor->moveTo(j->getJInput()->getMouseXPos() - 5, j->getJInput()->getMouseYPos() - 5);

		if (j->getJInput()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
			//j->addElement(new Image("2.bmp", 5, 5));
		}




		if (j->getJInput()->isKeyDown(SDL_SCANCODE_D)) {
			r->moveBy(speed, 0);
			r->setImage(walk1);
			frame = (int)(time / 5) % 7;
			r->setBlit((frame % 7) * 23, 0, 23, 4);
			r->setFlip(SDL_FLIP_NONE);
		}
		else if (j->getJInput()->isKeyDown(SDL_SCANCODE_A)) {
			r->moveBy(-speed, 0);
			r->setImage(walk1);
			r->setFlip(SDL_FLIP_HORIZONTAL);
			frame = (int)(time / 5) % 7;
			r->setBlit((frame % 7) * 23, 0, 23, 41);
		}
		else {
			r->setImage(idle);
			frame = (int)(time / 5) % 6;
			r->setBlit((frame % 3) * 32, ((frame)>2) * 50, 32, 41);
		}
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_SPACE) && jump <= 0) {
			if (r->getY() >= 388) {
				jump = 500;
			}
		}
		jump -= 60 * 20 * j->getTimeStep() / 1000.0f;
		if (jump < -260) {
			jump = -260;
		}
		r->moveBy(0, 90 - jump);

		if (r->getY() > 390) {
			r->moveTo(r->getX(), 390);
		}
		r->isCollidingAndAdjust(cursor);
		j->getJInput()->update();
		j->refreshScreen();
	}
}