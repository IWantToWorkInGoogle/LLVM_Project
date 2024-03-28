#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "sim.h"

#define FRAME_TICKS 50
#define INTENSE 5

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;

extern void app();

void setDead(int x, int y) {
	state[x][y] = false;
	simPutPixel(x, y, 0xFFFFFF);
}

void setAlive(int x, int y) {
	state[x][y] = true;
	simPutPixel(x, y, 0x000000);
}

void simSetRender() {
	for (int x = 0; x < SIM_X_SIZE; ++x) {
		for (int y = 0; y < SIM_Y_SIZE; ++y) {
			int r = simRand() % INTENSE;
			if (r) setDead(x,y);
			else setAlive(x,y);
		}
	}
	simFlush();
}

void simInit()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SIM_X_SIZE, SIM_Y_SIZE, 0, &Window, &Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
	srand(time(NULL));
	simSetRender();
    SDL_RenderClear(Renderer);
}

void simExit()
{
    SDL_Event event;
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

int main(void)
{
    simInit();
    app();
    simExit();
    return EXIT_SUCCESS;
}

void simFlush()
{
    SDL_PumpEvents();
    assert(SDL_TRUE != SDL_HasEvent(SDL_QUIT) && "User-requested quit");
    Uint32 cur_ticks = SDL_GetTicks() - Ticks;
    if (cur_ticks < FRAME_TICKS)
    {
        SDL_Delay(FRAME_TICKS - cur_ticks);
    }
    SDL_RenderPresent(Renderer);
}

void simPutPixel(int x, int y, int argb)
{
    assert(0 <= x && x < SIM_X_SIZE && "Out of range");
    assert(0 <= y && y < SIM_Y_SIZE && "Out of range");
    Uint8 a = argb >> 24;
    Uint8 r = (argb >> 16) & 0xFF;
    Uint8 g = (argb >> 8) & 0xFF;
    Uint8 b = argb & 0xFF;
    SDL_SetRenderDrawColor(Renderer, r, g, b, a);
    SDL_RenderDrawPoint(Renderer, x, y);
    Ticks = SDL_GetTicks();
}

int simRand()
{
    return rand();
}
