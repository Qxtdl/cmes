#include "../../../taulib/stdio.h"
#include "../../filesystem/fs.h"

void cat(int argc, char *argv[]) {
    if (fs_find(argv[0]) == FS_OK) {
        if (strcmp(g_returned_file.extension, "txt")) {
            puts("warning: file is not .txt\n");
        }
        for (u32 i = 0; i < g_returned_file.size; i++) {
            putc(read_disk(g_returned_file.data_ptr++));
        }
    } else puts("File not found\n");
}