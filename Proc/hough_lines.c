#include "image_modification.h"

#include <math.h>
#include <stdlib.h>

#include "display.h"

float thetaToRad (int theta)               // Converting theta to thetaRad
{
  float thetaRad = (theta * 3.14)/180;
  return thetaRad;
}
int rhoCalc (int x, int y , float theta)
{

  int rho = x * cosf(theta) + y * sinf(theta);
  return abs(rho);
}


int* boardMaxfinder(int* board, int height, int width)   //this function will find the hottest point in the hough space
{                                                        //wich also points to the degree of inclination of our board within the image
  int max = *board;                                      //so we record max and theta and store them in a 2 space intlist.
  int theta = 0;
  int* list = malloc(2);
  
  for (int i=0; i < height; i++)
    {
      for (int j = 0; j < width ; j++)
	{
	  if (max < board[i*width + j])
	    {
	      max = board [i*width +j];
	      theta = i;
	    }
	}
    }
  
  *list = max;
  *(list+1) = theta;
  return list;
}


SDL_Surface* greyScale (SDL_Surface* image_surface)                         //a basic greyscale function with an indiscriminate threshold
{                                                                           // to be replace by Otsu algorithm.
  for(int i = 0; i < image_surface->w; i++)
	{
		for(int j = 0; j < image_surface->h; j++)
		{
			Uint32 pixel = get_pixel(image_surface, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			float average = 0.3 * ((float) r) + 0.59 * ((float) g) + 0.11 * ((float) b);
			pixel = SDL_MapRGB(image_surface->format, average, average, average);
			put_pixel(image_surface, i, j, pixel);
		}
	}
  return image_surface;
  
}


int* rhoList (int* board , int height, int width, int theta, int max)      //this function will find the lines
                                                                          //distance from the origin corresponding to the theta and max values of the board
{
  int index = 0;
  int* list = malloc(sizeof(int) * height);
  int cooldown = 2;
  for (int i = 0 ; i < height ; i++)
    {
      if ((board[i*width + theta] >= max)&& (cooldown < 0))
	{
	  list[index] = i;
	  index++;
	  cooldown= 10;
	}
      cooldown--;
    }
  return list;
}


int* boardGeneration ( SDL_Surface *img, int height, int width)         //this is the hough algoritm, it compiles a theta by rho board also known as the hough space
{
  
  int max_distance = sqrt((height*height)+(width*width));
  int* board = calloc(max_distance*180,sizeof(int));
  
  for (int i = 0 ; i < height ; i++)
  {
    for (int j = 0; j < width ; j++)
      {
	Uint32 pixel = get_pixel (img,j,i);
	Uint8 r, g, b;
	SDL_GetRGB(pixel, img->format, &r, &g, &b);
	if (r<25 && g<25 && b<25)
	  {
	    for(int theta = 0 ; theta <= 180 ; theta++)
	      {
		float thetaRad = thetaToRad(theta);
		int rho = rhoCalc(j,i,thetaRad);
		board[rho*180 + theta]+=1;
	      }
	  }	    
      }
  }

 /* 
    for (int i = 0; i < 180; i++)            //a display algorithm that allowed me to visualise heat points in the hough space to be able to programm the rhoList compiler.
    {
      printf("%d :" , i);
      
      for (int j = 0; j < max_distance; j++)
	{
	if (board[j*180+ i] >250)             // the XX value needs to be replaced by a threshold for heat points to be more clearly displayed in a sea of low votes.
	    {
	      //printf(" rho = %d : %d  ", j,board[j*180+ i]) ;
	      printf("%d " ,board[j*180+ i] );
	    }
	  else
	    {
	      printf(" ");
	    }
	  
	  
	  //printf("%d", (board[j*180+ i]));
	}
      printf("\n");
    }
  printf("        ");
  for (int i = 0; i< max_distance; i++)
    {
      printf("%d ",i);
      }

*/  
  
  return(board);
}



int main()
{
  //declaration o base values
  SDL_Surface *img;
  img = load_image("test");                       //imgage loading
  img = greyScale (img);                              //greyscale application
  int width = img -> w;                               //detection of height
  int height= img -> h;                               //detection of width
  int rhoMax = sqrt(width*width + height*height);     //calculating of rhoMax through the Pythagoras Theorem
  int thetaMax = 180;                                     
  
  int* board = boardGeneration(img, height, width);   //creation and compilation of hough space board

  int* maxNtheta = boardMaxfinder(board, rhoMax, thetaMax);
  int max = *maxNtheta;
  int theta = *(maxNtheta + 1);
  if (theta>0)
    {
      //rotate board launch board generation again.
      board =  boardGeneration(img, height, width);
      maxNtheta = boardMaxfinder(board, rhoMax, thetaMax);
      max = *maxNtheta;
      theta = *(maxNtheta + 1);
    }
  int verticalTheta = 0;
  //int horizontalTheta =90;
  
  //int* horizontalRho = rhoList(board, rhoMax, thetaMax, horizontalTheta , max/2);  // compilation of horizontal line limits
  int* verticalRho = rhoList(board, rhoMax, thetaMax, verticalTheta , max/2);      // compilation of vertical line limits
  int* horizontalRho = verticalRho;
  /*for(int i = 0; i<9;i++){
        printf("%d \n", horizontalRho[i]);
  }*/
  char label[8] = "outp/X_Y";                                                     // label is the save file location plus X Y values corresponding to coordinates of case
  for(int i = 0; i<9 ; i++)
    {
      for(int j = 0; j<9 ; j++)
	{
	  label[7] = (char)(i+48);
	  label[5] = (char)(j+48);
	  imageCrop(img,*(i+horizontalRho),*(j+verticalRho),*((i+1)+horizontalRho),*((j+1)+verticalRho),label); //cropping and saving function found in image_modification.c
	}
    }
  
}
