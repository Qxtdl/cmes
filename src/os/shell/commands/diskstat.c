#include "../../../taulib/globals.h"
#include "../../filesystem/fs.h"

void diskstat(int argc, char *argv[]) {
    bool is_disk_formatted = read_disk(FS_FORMATTED);
    u32 last_created_file_header_address;
    read_n_disk(HEADER_LAST_CREATED_FILE_NODE_ADDRESS_PTR, sizeof(u16), (u8 *)&last_created_file_header_address);
    file_node_t last_created_file;
    read_n_disk(last_created_file_header_address, sizeof(file_node_t), (u8 *)&last_created_file);

    printf("Disk Formatted: %s\n"
            "Last Created File %x\n"
            "Dir %x",
            is_disk_formatted ? "yes" : "no", last_created_file_header_address, g_dir_addr);
}