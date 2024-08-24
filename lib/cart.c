#include <cart.h>

typedef struct
{
    char filename[1024];
    u32 rom_size;
    u8 *rom_data;
    rom_header *header;
} cart_context;

static cart_context cartContext;

// From The Cycle-Accurate Game Boy Docs
static const char *ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 Unnused",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 Unnused",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A Unnused",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E Unnused",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 Unnused",
    "0x15 Unnused",
    "0x16 Unnused",
    "0x17 Unnused",
    "0x18 Unnused",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F Unnused",
    "MBC6",
    "0x21 Unnused",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char *LICENSEE_CODES[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"};

const char *cart_licensee_name()
{
    if (cartContext.header->manufacturer_code <= 0xA4)
    {
        return LICENSEE_CODES[cartContext.header->licensee_code];
    }

    return "UNKNOWN";
}

const char *cart_type_name()
{
    if (cartContext.header->type <= 0x22)
    {
        printf("Cart header type: %s\n", cartContext.header->type );
        return ROM_TYPES[cartContext.header->type];
    }

    return "UNKNOWN";
}

bool cart_load(char *cart)
{
    snprintf(cartContext.filename, sizeof(cartContext.filename), "%s", cart);
    FILE *file_pointer = fopen(cart, "r");

    if (!file_pointer)
    {
        printf("Failed to open: %s\n", cart);
        return false;
    }

    printf("Opened: %s\n", cartContext.filename);

    fseek(file_pointer, 0, SEEK_END);
    cartContext.rom_size = ftell(file_pointer);

    rewind(file_pointer);

    cartContext.rom_data = malloc(cartContext.rom_size);
    fread(cartContext.rom_data, cartContext.rom_size, 1, file_pointer);
    fclose(file_pointer);

    cartContext.header = (rom_header *)(cartContext.rom_data + 0x100);
    cartContext.header->title[15] = 0;

    printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", cartContext.header->title);
    printf("\t Type     : %2.2X (%s)\n", cartContext.header->type, cart_type_name());
    printf("\t ROM Size : %d KB\n", 32 << cartContext.header->rom_size);
    printf("\t RAM Size : %2.2X\n", cartContext.header->ram_size);
    printf("\t LIC Code : %2.2X (%s)\n", cartContext.header->licensee_code, cart_licensee_name());
    printf("\t ROM Vers : %2.2X\n", cartContext.header->version);

    u16 x = 0;
    for (u16 i = 0x0134; i <= 0x014C; i++)
    {
        x = x - cartContext.rom_data[i] - 1;
    }

    printf("\t Checksum : %2.2X (%s)\n", cartContext.header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");

    return true;
}

u8 cart_read(u16 address){
  // ROM ONLY
  return cartContext.rom_data[address];
}

void cart_write(u16 address, u8 value){
  NOT_IMPLEMENTED
}

