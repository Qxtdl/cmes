#include "../../filesystem/fs.h"

void cd(int argc, char *argv[]) {
    if (!strcmp(argv[0], "<")) {
        fs_set_dir(g_old_dir_addr);
        return;
    }
    if (fs_find(argv[0]) == FS_BAD)
        puts("folder not found");
    fs_set_dir(g_returned_file.self_addr);
}