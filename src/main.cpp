/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <sstream>
#include "LTexture.h"
#include "LTimer.h"
#include "SDLHelper.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int deltaX = 10;
const int deltaY = 10;

int posX = 0;
int posY = 0;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
//SDL_Window* gWindow = NULL;

//The window renderer
//SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[ 4 ];
LTexture*  gSpriteSheetTexture = NULL;


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !gSpriteSheetTexture->loadFromFile( "dots.png" ) )
	{
		cout << "Failed to load sprite sheet texture!" << endl;
		success = false;
	}
	else
	{
		//Set top left sprite
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w = 100;
		gSpriteClips[ 0 ].h = 100;

		//Set top right sprite
		gSpriteClips[ 1 ].x = 100;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w = 100;
		gSpriteClips[ 1 ].h = 100;

		//Set bottom left sprite
		gSpriteClips[ 2 ].x =   0;
		gSpriteClips[ 2 ].y = 100;
		gSpriteClips[ 2 ].w = 100;
		gSpriteClips[ 2 ].h = 100;

		//Set bottom right sprite
		gSpriteClips[ 3 ].x = 100;
		gSpriteClips[ 3 ].y = 100;
		gSpriteClips[ 3 ].w = 100;
		gSpriteClips[ 3 ].h = 100;
	}

	return success;
}

void close()
{
	//Free loaded images
	//cout << "texture free " << endl;
	gSpriteSheetTexture->free();

	//Destroy window
	//cout << "sdlhelper free" << endl;
	SDL_DestroyRenderer( SDLHelper::renderer );
	SDL_DestroyWindow( SDLHelper::window );
	SDLHelper::free();
	//gWindow = NULL;
	//gRenderer = NULL;

	//Quit SDL subsystems
	//cout << "subsystems quit" << endl;
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
    bool inited = SDLHelper::init(640, 480);
    gSpriteSheetTexture = new LTexture();
    LTimer fpsTimer;
    int countedFrames = 0;
    fpsTimer.start();
	//Start up SDL and create window
	if(!inited)
	{
		cout <<  "Failed to initialize!" << endl;
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
			    //cout <<"loop" << endl;
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
				    //cout << "poll event" << endl;
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_RIGHT:
                            case SDLK_d:
                                if(posX + deltaX + gSpriteClips[0].w <= SDLHelper::WINDOW_WIDTH)
                                {
                                    posX += deltaX;
                                }
                                break;
                            case SDLK_LEFT:
                            case SDLK_a:
                                if(posX - deltaX >= 0)
                                {
                                    posX -= deltaX;
                                }
                                break;
                            case SDLK_UP:
                            case SDLK_w:
                                if(posY - deltaY >= 0)
                                {
                                    posY -= deltaY;
                                }
                                break;
                            case SDLK_DOWN:
                            case SDLK_s:
                                if(posY + deltaY + gSpriteClips[0].h <= SDLHelper::WINDOW_HEIGHT)
                                {
                                    posY += deltaY;
                                }
                                break;
                        }
                        if(e.key.keysym.sym == SDLK_ESCAPE)
                            quit = true;
                    }
				}
				stringstream title;

				float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
				if( avgFPS > 2000000 )
				{
					avgFPS = 0;
				}

				cout << "FPS " << avgFPS << endl;
				//SDL_SetWindowTitle(SDLHelper::window, (char*)fpsTimer.getTicks());

				//Clear screen
				SDL_SetRenderDrawColor( SDLHelper::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( SDLHelper::renderer );

				//Render top left sprite
				gSpriteSheetTexture->render( posX, posY, &gSpriteClips[ 0 ] );

				//Render top right sprite
				gSpriteSheetTexture->render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

				//Render bottom left sprite
				gSpriteSheetTexture->render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

				//Render bottom right sprite
				gSpriteSheetTexture->render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

				//Update screen
				SDL_RenderPresent( SDLHelper::renderer );
				++countedFrames;
			}
		}
	}

    //cout << "loop end" << endl;
	//Free resources and close SDL
	close();

	return 0;
}
