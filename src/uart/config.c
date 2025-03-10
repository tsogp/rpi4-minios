#include "include/uart/config.h"
#include "include/utils/size.h"
#include "include/string/string.h"

config cf = {
        115600,
        &data_bits[3],
        &stop_bits[0],
        &parities[0],
        &handshakes[0]
};

const arg_config *find_arg_config(const arg_config *dest, const char *name, size_t size) {;
        for (size_t i = 0; i < size; i++) {
                if (strcmp(name, dest[i].name) == 0) {
                        return &dest[i];
                }
        }

        return NULL;
}

const arg_config *find_data_bits_args(const char *name) {
        return find_arg_config(data_bits, name, DATA_BITS_ARGS_SIZE);
}

const arg_config *find_stop_bits_args(const char *name) {
        return find_arg_config(stop_bits, name, STOP_BITS_ARGS_SIZE);
}

const arg_config *find_parities_args(const char *name) {
        return find_arg_config(parities, name, PARITIES_ARGS_SIZE);
}

const arg_config *find_handshakes_args(const char *name) {
        return find_arg_config(handshakes, name, HANDSHAKES_ARGS_SIZE);
}

void update_config(uint32_t baud_rate, const arg_config *data_bit, const arg_config *stop_bit, const arg_config *parity, const arg_config *handshake) {
        if (baud_rate != 0) {
                uart_puts("Baud Rate set to ");
                uart_dec(baud_rate);
                uart_puts(".\n");
                cf.baud_rate = baud_rate;
        }

        if (data_bit != NULL) {
                uart_puts("Data Bit amount set to ");
                uart_puts(data_bit->name);
                uart_puts(".\n");
                cf.data_bit = data_bit;
        }

        if (stop_bit != NULL) {
                uart_puts("Stop Bit amount set to ");
                uart_puts(stop_bit->name);
                uart_puts(".\n");
                cf.stop_bit = stop_bit;
        }

        if (parity != NULL) {
                uart_puts("Parity set to ");
                uart_puts(parity->name);
                uart_puts(".\n");
                cf.parity = parity;
        }

        if (handshake != NULL) {
                uart_puts("Handshake set to ");
                uart_puts(handshake->name);
                uart_puts(".\n");
                cf.handshake = handshake;
        }
}