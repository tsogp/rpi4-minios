#ifndef ASM2_CLEAR_H
#define ASM2_CLEAR_H

#define CLEAR_NAME "clear"

#define CLEAR_DESC \
        "Usage: clear \n" \
        "Clear the terminal window (scroll down to current position of the cursor)\n\n" \
        "Example:\n" \
        "  clear            clears the terminal window\n"

err_code clear_cmd_handler();

#endif