#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

SDL_Surface* createSurface(int height, int width)
{
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;



    surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
    return surface;
}

void freeSDL(SDL_Surface* image)
{
  SDL_FreeSurface(image);
}



/*
void imageCrop (SDL_Surface* img , int leftBorder , int topBorder , int rightBorder, int bottomBorder)
{
  SDL_Surface* image = img;
  SDL_Surface* surface = createSurface(topBorder-bottomBorder,rightBorder-leftBorder);
  for (int i= topBorder; i< bottomBorder ; i++)
    {
      for(int j=leftBorder; i < rightBorder ; j++)
	{
	  Uint32 pixel = get_pixel(image, j,i);
	  put_pixel(surface,j-leftBorder,i-topBorder, pixel);
	}
    }
  SDL_SaveBMP(surface,"savetest.bmp");
  
  }
*/


/*
int main()
{
    	SDL_Surface* image_surface;
    	SDL_Surface* screen_surface = NULL;
    	init_sdl();
    	image_surface = load_image("my_image.jpg");
    	display_image(image_surface);
    	wait_for_keypressed();
	
    	SDL_FreeSurface(image_surface);
	    SDL_FreeSurface(screen_surface);
	
    	return 0;
}
*/
