#include "../../filesystem/fs.h"

void mdf(int argc, char *argv[]) {
    fs_find(argv[0]);
    if (*argv[1] != '*')
        strcpy(g_returned_file.name, argv[1]);
    if (*argv[2] != '*')
        strcpy(g_returned_file.extension, argv[2]);
    if (*argv[3] != '*')
        g_returned_file.size = hex_str_to_u32(argv[3]);
    if (*argv[4] != '*')
        g_returned_file.data_ptr = hex_str_to_u32(argv[4]);

    disk_n_write(g_returned_file.self_addr, sizeof(file_node_t), (u8 *)&g_returned_file);
}