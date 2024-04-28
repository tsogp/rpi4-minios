#ifndef ASM2_SETCOLOR_H
#define ASM2_SETCOLOR_H

#include "include/gpio.h"

#define SETCOLOR_NAME "setcolor"

#define SETCOLOR_DESC \
        "Usage: setcolor [OPTION]...\n" \
        "Set text color, and/or background color of the console to one of the following colors: BLACK, RED, GREEN, " \
        "YELLOW, BLUE, PURPLE, CYAN, WHITE, DEFAULT (default text or background color)\n\n" \
        " -t [TEXT_COLOR]        set the text color to TEXT_COLOR\n" \
        " -b [TEXT_COLOR]        set the background color to TEXT_COLOR\n\n" \
        "Example:\n"  \
        "  setcolor -t YELLOW               set the text color to yellow\n" \
        "  setcolor -b YELLOW -t WHITE      set the text color to white and background to yellow\n"

err_code setcolor_cmd_handler();

err_code flag_setter(const char **args, uint8_t *flags, uint8_t arg_no);

#endif
