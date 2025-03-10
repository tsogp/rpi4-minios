#ifndef ASM2_UARTCONF_H
#define ASM2_UARTCONF_H

#include "include/error/error_code.h"

#define UARTCONF_NAME "uartconf"

#define UARTCONF_DESC \
        "Usage: uartconf [OPTION]...\n" \
        "Configure the settings of the PL011 UART protocol during runtime.\n" \
        " -b [BAUD_RATE]         Set the Baud Rate of PL011 UART to BAUD_RATE.\n" \
        "                        Stable options are 9600, 19200, 38400, 57600, and 115200 bits per second.\n" \
        "                        Other values can be provided, but their stability is not guaranteed.\n" \
        " -d [DATA_BITS]         Configures the number of data bits to DATA_BITS. Only available options of\n"\
        "                        DATA_BITS are 5, 6, 7 or 8.\n"               \
        " -s [STOP_BITS]         Configures the number of stop bits to STOP_BITS. Only available options of\n"\
        "                        STOP_BITS are 1 or 2.\n"                     \
        " -p [PARITY_CONFIG]     Sets the parity configuration. Only available options of\n"\
        "                        PARITY_CONFIG are NONE, EVEN or ODD.\n"      \
        " -h [PROTOCOL]          Sets the handshaking configuration. Only available options of\n"\
        "                        PROTOCOL are ENABLED or DISABLED.\n"               \
        "Example:\n"  \
        "  uartconf -b 19200                set baud rate to 9600\n" \
        "  uartconf -d 6 -s 2 -p NONE       set the number of data bits to 6, enable 2 stop bits and disable parity\n"

err_code uartconf_cmd_handler();

#endif //ASM2_UARTCONF_H
