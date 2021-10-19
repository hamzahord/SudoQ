#include <err.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"


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

void SDL_FreeSurface(SDL_Surface *surface);


void makehisto(SDL_Surface *image, int rows,int cols, unsigned long *histo) // used in otsu
{
    for(int i =0; i<rows; i++)
    {

        for(int j =0; i<cols; i++)
        {

            Uint32 pixel = get_pixel(image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            histo[r] +=1;
        }
    }
} 

int otsu(SDL_Surface *image, int rows, int cols) // used in Blackandwhite
{
    unsigned long *histo = calloc(256,sizeof(unsigned long));
    makehisto( image, rows,cols,histo);

    unsigned long nb_pxl= (unsigned long)rows*cols;
    unsigned long top = 256;
    unsigned long wF = 0;
    unsigned long wB = 0;
    unsigned long max =0;
    unsigned long sumB=0 ;
    unsigned long sum1=0 ;
    int level= 0;

    for(unsigned long j = 1; j<top;j++)
    {
        sum1 = j*histo[j];
    }
    for(int i =0; i<256; i++)
    {

        wB+=histo[i];
        if(wB==0){
            continue;
        }

        wF = nb_pxl -wB;
        if(wF==0){
            break;
        }

        sumB +=  (i*histo[i]);

        unsigned long mB = sumB/wB;
        unsigned long mF = (sum1-sumB)/wF;

        float val = wB*wF*(mB-mF)*(mB-mF);
            if(val>=max)
            {
                level= i;
                max = val;
            }
    }
    return level;
}


int BlackandWhite(char source[])
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    init_sdl();
    image_surface = load_image(source);
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    int height = image_surface->h;
    int width = image_surface->w;
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint8 average = 0.3 * r + 0.59 * g + 0.11 * b;
            r = average;
            g = average;
            b = average;
            Uint32 new_pixel = SDL_MapRGB(image_surface->format, r, g, b);
            put_pixel(image_surface,i,j,new_pixel);
        }
    }
    
    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    int tresh = otsu(image_surface, width, height);

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if (r >= tresh)
            {
                r = 255;
                g = 255;
                b = 255;
            }
            else
            {
                r = 0;
                g = 0;
                b = 0;
            }

            Uint32 new_pixel = SDL_MapRGB(image_surface->format, r, g, b);
            put_pixel(image_surface,i,j,new_pixel);    
        }
    }
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    return 0;
}


int main()
{
    BlackandWhite("my_image.jpg");
    return 0;
}
