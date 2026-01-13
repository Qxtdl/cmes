#include "../../filesystem/fs.h"
#include "../../../taulib/heap.h"

void run(int argc, char *argv[]) {
    u8 *program = NULL;
    if (fs_find(argv[0]) == FS_OK) {
        if (strcmp(g_returned_file.extension, "exe")) {
            puts("warning: file is not .exe\n");
        }
        if (strcmp(g_returned_file.extension, "pcval")) {
            u32 pc_target = 0;
            read_n_disk(g_returned_file.data_ptr, 2, (u8 *)&pc_target);
            asm volatile (
                "jalr  zero, %[addr], 0\n"
                :
                : [addr] "r" (pc_target)
                : "memory"
            );
        }

        program = malloc(g_returned_file.size);
        if (!program) {
            puts("OUT OF HEAP\n");
            return;
        }

        read_n_disk(g_returned_file.data_ptr, g_returned_file.size, program);

        ((void (*)(void))program)();
    } else puts("File not found\n");
}