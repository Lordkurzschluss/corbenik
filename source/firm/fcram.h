#ifndef __FCRAM_H
#define __FCRAM_H

// File to keep track of all the fcram offsets in use.
// It provides an easy overview of all that is used.

#include <stdint.h>

#include "../std/unused.h"

extern void *fcram_temp;

// Space between most of the locations
#define FCRAM_SPACING 0x100000

// Start of the space we use
#define FCRAM_START 0x24000000

// firm.c
#define FCRAM_FIRM_LOC FCRAM_START
#define FCRAM_TWL_FIRM_LOC (FCRAM_START + FCRAM_SPACING)  // Double size
#define FCRAM_AGB_FIRM_LOC (FCRAM_START + FCRAM_SPACING * 3)

// patch.c
#define FCRAM_MEMORY_LOC (FCRAM_START + FCRAM_SPACING * 4)

_UNUSED static uint8_t *memory_loc = (uint8_t *)FCRAM_MEMORY_LOC;
_UNUSED static void *current_memory_loc;

#endif