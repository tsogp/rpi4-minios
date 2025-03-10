#ifndef ASM2_SHOWINFO_H
#define ASM2_SHOWINFO_H

#include "include/gpio.h"

#define SHOWINFO_NAME "showinfo"

#define SHOWINFO_DESC \
        "Usage: showinfo \n" \
        "Show board revision info and board MAC address\n\n" \
        "Example:\n" \
        "  showinfo         shows the board info \n"

err_code showinfo_cmd_handler();

void fill_board_revision(volatile uint32_t val);

void fill_mac_addr(volatile uint32_t first_chunk, volatile uint32_t second_chunk);

#endif
