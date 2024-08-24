#pragma once

#include <common.h>

typedef struct
{
    bool paused;
    bool running;
    u64 ticks;
} emulator_context;

int emulator_run(int argc, char **argv);

emulator_context *get_emulator_context();

void emulator_cycles(int cpu_cycles);
