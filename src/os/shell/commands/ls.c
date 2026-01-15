#include "../../filesystem/fs.h"
#include "../../../taulib/stdio.h"

void ls(int argc, char *argv[]) {
    // int i = 1;
    // while (fs_get_file_at(i++) != FS_BAD) {
    //     printf("%s.%s : %x %x\n", g_returned_file.name, g_returned_file.extension, g_returned_file.size, g_returned_file.data_ptr);
    // }

    fs_loop_dir(true);
    while (fs_loop_dir(false)) {
        printf("%s.%s\n", g_returned_file.name, g_returned_file.extension);
    }
}