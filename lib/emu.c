#include <stdio.h>
#include <emu.h>
#include <cart.h>
#include <cpu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
  Emu components:

  |Cart|
  |CPU|
  |Address Bus|
  |PPU|
  |Timer|

*/

static emulator_context context;

emulator_context *get_emulator_context()
{
    return &context;
}

void delay(u32 ms)
{
    SDL_Delay(ms);
}

int emulator_run(int argumentCount, char **argumentValues)
{
    if (argumentCount < 2)
    {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argumentValues[1]))
    {
        printf("Failed to load ROM file: %s\n", argumentValues[1]);
        return -2;
    }

    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL INIT\n");
    TTF_Init();
    printf("TTF INIT\n");

    cpu_init();

    context.running = true;
    context.paused = false;
    context.ticks = 0;

    while (context.running)
    {
        if (context.paused)
        {
            delay(10);
            continue;
        }

        if (!cpu_step())
        {
            printf("CPU Stopped\n");
            return -3;
        }

        context.ticks++;
    }

    return 0;
}
