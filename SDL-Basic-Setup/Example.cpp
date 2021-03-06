/******************************
*Filename: Example.cpp
*Author: Jory Leech
*Description: Various examples of how to use JEngine.
*Run any of these in the main method. 
*Warning: Use only one method per program, this is due to the way JEngine is controlled. 
******************************/
#include "JEngine.h";
#include <iostream>
/********************
*Name: ImageExample
*Params: None
*Description: An example of how to load an image using JEngine
*Notes: None
********************/
void ImageExample()
{
	JEngine * engine = new JEngine();
	//Required to initilize the window. 
	engine->init("Image Example", 640, 480, 60);
	engine->setMaxFrameRate(60);
	//Creates a pointer to an image, and fills it with an image from the url at the position.
	Image * image = new Image("Resources/Images/ImageExample1.png", 200, 200);
	//This adds the image to the rendering list. Without this you own the image but it will not draw to the screen.
	engine->addElement(image);
	//getQuit is an important method and the only way to check if the x button was clicked. 
	while (!engine->getQuit())
	{
		engine->refreshScreen();
	}
	delete(engine);
}
/********************
*Name: InputExample
*Params: None
*Description: An example of how to use keyboard input to move an object using JEngine
*Notes: None
********************/
void InputExample()
{
	JEngine * engine = new JEngine();
	engine->init("Image Example", 1920, 1080, 60);
	engine->setMaxFrameRate(2 );
	int speed = 200;
	Image * image = new Image("Resources/Images/ImageExample1.png", 200, 200);
	engine->addElement(image);
	JInput * inputController = engine->getJInput();
	while (!engine->getQuit())
	{
		if (inputController->isKeyDown(SDL_SCANCODE_W)) {
			image->moveBy(0, -speed);
		}
		if (inputController->isKeyDown(SDL_SCANCODE_A)) {
			image->moveBy(-speed, 0);
		}
		if (inputController->isKeyDown(SDL_SCANCODE_S)) {
			image->moveBy(0,speed);
		}
		if (inputController->isKeyDown(SDL_SCANCODE_D)) {
			image->moveBy(speed,0);
		}
		std::cout << engine->getTimeStep();
		engine->refreshScreen();
	}
	delete(engine);
}
static int forceRenderTextureThread(void* ptr)
{
	JRenderer* text = (JRenderer*)ptr;
	std::cout << "PTR:" << ptr << "\n";
	text->forceRenderTexture();
	return 0;
}
/*****************************
*Name: renderingThreadingTest1
*Params: None
*Description: Test whether using multiple threads to render non-overlapping images will increase processing time
*Notes: N/A
******************************/
void renderingThreadingTest1() {
	JEngine * engine = new JEngine();
	engine->init("Image Example", 1920, 1080, 60);
	engine->setMaxFrameRate(-1);
	//engine->setWindowFullScreen();
	const int numTiles = 10;
	const int numThreads = 2;
	Image * image = new Image("Resources/Images/ImageExample1.png", 200, 200);
	
	//An Array of pointers to images
	Image* tiles[numTiles] = {};
	JRenderer* renderTexture[numThreads] = {};
	SDL_Thread* threads[numThreads] = {};
	
	for (int i = 0; i < numTiles; i++) {
		tiles[i] = new Image("Resources/Images/renderingThreadTestTile.png", (32 * (i )), 0);
		
	}


	for (int i = 0; i < numThreads; i++) {
		renderTexture[i] = new JRenderer(0, 0, 1920, 1080);
		for (int y = 0; y < numTiles / numThreads; y++) {
			renderTexture[i]->addElement(tiles[((numTiles/numThreads)*i)+y]);
		}
		renderTexture[i]->setAutoRender(false);
		engine->addElement(renderTexture[i]);

		
	}
	engine->addElement(image);
	std::cout << "Starting Game Loop \n";
	for (int i = 0; i < numThreads; i++) {
		//	threads[i] = SDL_CreateThread(forceRenderTextureThread, "ForceRender" + i, (void *)renderTexture[i]);
		renderTexture[i]->forceRenderTexture();
	}
	while (!engine->getQuit()) {
		engine->refreshScreen();
		//std::cout << engine->getTimeStep()<<"\n";
		for (int i = 0; i < numThreads; i++) {
			//threads[i] = SDL_CreateThread(forceRenderTextureThread, "ForceRender" + i, (void *)renderTexture[i]);	
		}
		image->moveBy(50,50);
		for (int i = 0; i < numThreads; i++) {
			int x;
			if (threads[i] != NULL) {
				SDL_WaitThread(threads[i], &x);
			}
		}
	}

	delete(engine);
}


int main(int argc, char* args[])
{
	renderingThreadingTest1();
	return 0;
}
