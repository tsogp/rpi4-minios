#ifndef ASM2_CONFIG_H
#define ASM2_CONFIG_H

#include "include/gpio.h"
#include "include/error/error_code.h"
#include "include/uart/uart0.h"

typedef struct arg_config {
    const char* name;
    const uint16_t value;
} arg_config;

#define DATA_BITS_ARGS_SIZE 4

static const arg_config data_bits[] = {
        {"5", UART0_LCRH_WLEN_5BIT},
        {"6", UART0_LCRH_WLEN_6BIT},
        {"7", UART0_LCRH_WLEN_7BIT},
        {"8", UART0_LCRH_WLEN_8BIT},
};

const arg_config *find_data_bits_args(const char *name);

#define STOP_BITS_ARGS_SIZE 2

static const arg_config stop_bits[] = {
        {"1", 0},
        {"2", UART0_LCRH_STP2},
};

const arg_config *find_stop_bits_args(const char *name);

#define PARITIES_ARGS_SIZE 3

static const arg_config parities[] = {
        {"NONE", 0},
        {"ODD", UART0_LCRH_PEN},
        {"EVEN", UART0_LCRH_PEN | UART0_LCRH_EPS},
};

const arg_config *find_parities_args(const char *name);

#define HANDSHAKES_ARGS_SIZE 3

static const arg_config handshakes[] = {
        {"DISABLED", 0},
        {"CTS", UART0_CR_CTSEN},
        {"RTS", UART0_CR_RTSEN},
};

const arg_config *find_handshakes_args(const char *name);

const arg_config *find_arg_config(const arg_config *dest, const char* name, size_t size);

typedef struct config {
    uint32_t baud_rate;
    const arg_config *data_bit;
    const arg_config *stop_bit;
    const arg_config *parity;
    const arg_config *handshake;
} config;

static config cf = {
        115600,
        &data_bits[3],
        &stop_bits[0],
        &parities[0],
        &handshakes[0]
};

#endif //ASM2_CONFIG_H
