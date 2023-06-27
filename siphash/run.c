#include "ulcg.h"
#include "unif01.h"
#include "bbattery.h"
#include "siphash.h"

static uint8_t siphash_key[16] = {
    0x6d, 0xe6, 0xfb, 0x87, 0x04, 0x6f, 0x26, 0x43, 0xbf, 0x08, 0x51, 0xe0, 0x86, 0x04, 0x91, 0x31
};

static uint64_t siphash_counter = 0;

static unsigned int siphash_gen(void) {
    uint64_t out;
    siphash(
        (void*)&siphash_counter, sizeof siphash_counter,
        (void*)siphash_key,
        (uint8_t*)(void*)&out, sizeof out
    );
    ++siphash_counter;
    return (unsigned int)out;
}

int main (void)
{
   unif01_Gen *gen = unif01_CreateExternGenBits("siphash-2-4", siphash_gen);
   bbattery_BigCrush (gen);
   return 0;
}
