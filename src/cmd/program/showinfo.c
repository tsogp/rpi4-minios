#include "include/error/error_code.h"
#include "include/cmd/program/showinfo.h"
#include "include/cmd/cmd.h"
#include "include/string/string.h"
#include "include/cmd/constants.h"
#include "include/mbox.h"

#include "include/uart/uart0.h"

void fill_board_revision(volatile uint32_t val, char* buf) {
        bool leading_zero = true;
        for (int pos = 28; pos >= 0; pos = pos - 4) {
                char digit = (val >> pos) & 0xF;

                digit += (digit > 9) ? (-10 + 'A') : '0';

                if (digit == '0' && leading_zero) {
                        continue;
                } else {
                        leading_zero = false;
                }

                *buf++ = digit;
        }

        *buf = '\0';
}

void fill_mac_addr(volatile uint32_t first_chunk, volatile uint32_t second_chunk, char *buf) {
        uint8_t fill_semicolon = 0;
        bool skip_first = true;

        for (int pos = 12; pos >= 0; pos = pos - 4) {
                char digit = (first_chunk >> pos) & 0xF;

                digit += (digit > 9) ? (-10 + 'A') : '0';
                if (!skip_first && fill_semicolon % 2 == 0) {
                        *buf++ = ':';
                }

                if (skip_first) {
                        skip_first = false;
                }

                *buf++ = digit;
                fill_semicolon = (fill_semicolon + 1) % 2;
        }

        for (int pos = 28; pos >= 0; pos = pos - 4) {
                char digit = (second_chunk >> pos) & 0xF;

                digit += (digit > 9) ? (-10 + 'A') : '0';
                if (fill_semicolon % 2 == 0) {
                        *buf++ = ':';
                }

                *buf++ = digit;
                fill_semicolon = (fill_semicolon + 1) % 2;
        }
}

err_code showinfo_cmd_handler() {
        if (strtok(NULL, CMD_ARGS_SEPARATOR) != NULL) {
                return invalid_cmd_usage(&cmds_buf[CLEAR]);
        }

        char board_revision[BOARD_REVISION_SIZE + 1], mac_addr[MAC_ADDRESS_SIZE];

        mBuf[0] = 11 * 8;
        mBuf[1] = MBOX_REQUEST;

        mBuf[2] = 0x00010002;
        mBuf[3] = 4;
        mBuf[4] = 0;
        mBuf[5] = 0;

        mBuf[6] = 0x00010003;
        mBuf[7] = 6;
        mBuf[8] = 0;
        mBuf[9] = 0;
        mBuf[10] = 0;

        if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
//                uart_puts("\nResponse Code for whole message: ");
//                uart_hex(mBuf[1]);

//                uart_puts("\n+ Response Code in Message TAG: ");
//                uart_hex(mBuf[4]);
                fill_board_revision(mBuf[5], board_revision);
                uart_puts("Board Revision = ");
                uart_puts(board_revision);
                uart_puts("\n");

                fill_mac_addr(mBuf[10], mBuf[9], mac_addr);
//                uart_puts("\n+ Response Code in Message TAG: ");
//                uart_hex(mBuf[8]);
                uart_puts("MAC Address = ");
                uart_puts(mac_addr);
        } else {
                uart_puts("Error retrieving data.");
                return CMD_RUNTIME_ERROR;
        }

        return SUCCESS;
}

