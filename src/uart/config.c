#include "include/uart/config.h"
#include "include/utils/size.h"
#include "include/string/string.h"

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
