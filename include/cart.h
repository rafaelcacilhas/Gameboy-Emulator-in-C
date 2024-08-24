#pragma once

#include <common.h>
//  The Cycle-Accurate Game Boy Docs, pg. 51
typedef struct
{
    u8 entry[4];
    u8 logo[0x30]; // 48 bytes Nintendo Logo

    char title[16]; // Upper Case ASCII
    u16 manufacturer_code;

    u8 sgb_flag;
    u8 type;
    u8 rom_size;
    u8 ram_size;
    u8 destination_code;
    u8 licensee_code;
    u8 version;
    u8 checksum;
    u16 global_checksum;
} rom_header;

bool cart_load(char *cart);

u8 cart_read(u16 address);

void cart_write(u16 address, u8 value);
