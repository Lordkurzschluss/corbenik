#include <common.h>
#include <ctr9/io.h>
#include <ctr9/ctr_screen.h>
#include <ctr9/i2c.h>

#define PDN_GPU_CNT (*(volatile uint8_t *)0x10141200)

static volatile uint32_t *const a11_entry = (volatile uint32_t *)0x1FFFFFF8;

struct framebuffers* framebuffers = NULL;

void
screen_mode(uint32_t mode)
{
    uint32_t *screenInitAddress = (uint32_t *)0x24FFFC00;

    FILE *f = fopen(PATH_SCREENINIT_CODE, "r");
    fread(screenInitAddress, 1, fsize(f), f); // Read in the screeninit payload.
    fclose(f);

    // FIXME - At the moment, this seems mandatory to do full screeninit.

    // I get very fucked up results from just changing the framebuffer offsets
    // and display color mode. Until I figure out WHY a full screeninit has to
    // be performed, I have to do a full screeninit.

    // And no, 3dbrew didn't help. Partial init seems to be a superset of what
    // I was attempting.

    screenInitAddress[2] = 1; // Do a partial init.

    if (PDN_GPU_CNT == 1)
        screenInitAddress[2] = 0; // Do a full init.

	// FIXME - God awful syntactical hack.
    screenInitAddress[3] = ("\x40\x8F\xC0\xFF")[config->options[OPTION_BRIGHTNESS]];

    screenInitAddress[4] = mode; // Mode

    *a11_entry = (uint32_t)screenInitAddress;

    while (*a11_entry);

    if (!framebuffers) {
        framebuffers = malloc(sizeof(struct framebuffers));
        memcpy(framebuffers, framebuffers_cakehax, sizeof(struct framebuffers));
    }

    // Turn on backlight
    i2cWriteRegister(I2C_DEV_MCU, 0x22, 1 << 1);
}
