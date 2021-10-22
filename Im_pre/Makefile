# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: display BlackAndWhite

display: display.o

BlackAndWhite: pixel_operations.o BlackAndWhite.o

BlackAndWhite.o: pixel_operations.h

clean:
	${RM} *.o	
	${RM} *.d
	${RM} display
	${RM} BlackAndWhite

# END
