#include "../../../taulib/string.h"
#include "../../filesystem/fs.h"

#include <stdint.h>

void mkf(int argc, char *argv[]) {
    print_errcode(fs_create_new_file(!strcmp(argv[0], "format") ? NULL : argv[0], argv[1], argv[2], hex_str_to_u32(argv[3]), (u8 *)(uintptr_t)hex_str_to_u32(argv[4])));
}