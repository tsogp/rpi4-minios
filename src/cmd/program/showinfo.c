#include "include/error/error_code.h"
#include "include/cmd/program/showinfo.h"
#include "include/cmd/cmd.h"
#include "include/string/string.h"
#include "include/cmd/constants.h"
#include "include/mbox.h"

#include "include/uart/uart0.h"

void fill_board_revision(volatile uint32_t val) {
        bool leading_zero = true;
        for (int pos = 28; pos >= 0; pos = pos - 4) {
                char digit = (val >> pos) & 0xF;

                digit += (digit > 9) ? (-10 + 'A') : '0';

                if (digit == '0' && leading_zero) {
                        continue;
                } else {
                        leading_zero = false;
                }

                uart_sendc(digit);
        }
}

void fill_mac_addr(volatile uint32_t first_chunk, volatile uint32_t second_chunk) {
        for (int pos = 0; pos <= 24; pos = pos + 8) {
                uint8_t digit = (first_chunk >> pos) & 0xFF;

                char ch1 = digit & 0xF, ch2 = (digit >> 4) & 0xf;

                ch1 += (ch1 > 9) ? (-10 + 'A') : '0';
                ch2 += (ch2 > 9) ? (-10 + 'A') : '0';

                uart_sendc(ch2);
                uart_sendc(ch1);
                uart_sendc(':');
        }

        for (int pos = 0; pos <= 8; pos = pos + 8) {
                uint8_t digit = (second_chunk >> pos) & 0xFF;

                char ch1 = digit & 0xF, ch2 = (digit >> 4) & 0xf;

                ch1 += (ch1 > 9) ? (-10 + 'A') : '0';
                ch2 += (ch2 > 9) ? (-10 + 'A') : '0';

                uart_sendc(ch2);
                uart_sendc(ch1);
                if (pos != 8) {
                        uart_sendc(':');
                }
        }
}

err_code showinfo_cmd_handler() {
        if (strtok(NULL, CMD_ARGS_SEPARATOR) != NULL) {
                return invalid_cmd_usage(&cmds_buf[SHOWINFO]);
        }

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

                uart_puts("Board Revision = ");
                fill_board_revision(mBuf[5]);
                uart_puts("\n");

                uart_puts("MAC Address = ");
                fill_mac_addr(mBuf[9], mBuf[10]);
        } else {
                uart_puts("Error retrieving data.");
                return CMD_RUNTIME_ERROR;
        }

        return SUCCESS;
}

