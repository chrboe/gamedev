#include "SDLHelper.h"

SDL_Renderer* SDLHelper::renderer = NULL;
int SDLHelper::WINDOW_WIDTH = 0;
int SDLHelper::WINDOW_HEIGHT = 0;
SDL_Window* SDLHelper::window = NULL;
bool SDLHelper::quit = false;

bool SDLHelper::init(int window_width, int window_height)
{
	//Initialization flag
	bool success = true;

	SDLHelper::WINDOW_WIDTH = window_width;
	SDLHelper::WINDOW_HEIGHT = window_height;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout <<  "Warning: Linear texture filtering not enabled!" ;
		}

		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				cout <<  "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout <<  "SDL_image could not initialize! SDL_mage Error: " << IMG_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

SDL_Texture* SDLHelper::loadTextureFromFile(string path)
{

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Creates texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( SDLHelper::renderer, loadedSurface );
		if( newTexture == NULL )
		{
			cout <<  "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}

void SDLHelper::free()
{
    SDL_free(renderer);
    SDL_free(window);
}

SDLHelper::SDLHelper()
{
    quit = false;
    window = NULL;
    renderer = NULL;
}

SDLHelper::~SDLHelper()
{

}
