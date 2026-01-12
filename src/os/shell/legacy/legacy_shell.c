#include "../../../taulib/globals.h"
#include "../../../taulib/string.h"
#include "../../../taulib/stdio.h"
#include "../../filesystem/fs.h"

extern file_t g_returned_file;

void legacy_shell(void)
{
    puts("\nL> ");
    char* command = gets();

    if (!strcmp(command, "exit")) {
        return;
    }
    if (strcmp(command, "clear") == 0)
    {
        clear_tty
        *TTY_LOC = 0;
        return;
    }
    if (strncmp(command, "echo ", 5) == 0)
    {
        puts("\n");
        puts(command + 5);
        return;
    }
    if (strncmp(command, "eliza", 5) == 0)
    {
        puts("\nELIZA:How are you feeling today?\n");
        while (1)
        {
            char* input = gets();
            if (strstr(input, "bye"))
            {
                clear_tty
                break;
            }
            if (strstr(input, "sad") || strstr(input, "unhappy"))
                puts("\nELIZA: I'm sorry to hear that. Why do you think you feel this way?\n");
            else if (strstr(input, "happy") || strstr(input, "good"))
                puts("\nELIZA: That's great! What makes you feel happy?\n");
            else if (strstr(input, "mother") || strstr(input, "father") || strstr(input, "family"))
                puts("\nELIZA: Tell me more about your family.\n");
            else if (strstr(input, "i dont know"))
                puts("\nELIZA: Can you elaborate on that?\n");
            else if (strstr(input, "help"))
                puts("\nELIZA: How can I help you?\n");
            else
                puts("\nELIZA: Please, go on.\n");
        }
    }
    if (strcmp(command, "neofetch") == 0)
    {
        puts("\n");
        puts("OS: CMES\n");
        puts("CPU: Taurus RV22MS0\n");
        puts("GPU: TileGPU\n");
        puts("\n");
    }
    if (strncmp(command, "godword ", 8) == 0)
    {
        const char *wordlist[] = 
        {
            "linux", "riscv", "1 tick", "cmes", "osdev",
            "templeos", "bootloader", "cpu", "chatgpt",
            "eliza", "chatbot", "1 tick cpu", "windows", "asm", "c",
            "god", "says", "eliza", "precious", "maybe",
            "future", "0 tick", "virus", "async",
            "tick", "multitasking", "preemptive", "cooperative",
            "kernel", "userland", "mode", "supervisor", "machine",
            "predict", "prediction", "impossible", "gpu", "npu",
        };
        u8 amount = hex_to_u8(command + 8);

        puts("\nGod says:\n");
        for (u8 i = 0; i < amount; i++)
        {
            u8 index = *RANDOM_BYTE & (sizeof(wordlist) / sizeof(wordlist[0]));
            puts(wordlist[index]);
            if (i != amount - 1)
                putc(' ');
        }

        return;
    }
    if (!strncmp(command, "calc", 4)) {
        u8 result = 0;
        puts("\nFirst num: ");
        u8 first = dec_to_u8(gets());
        puts("\nSecond num: ");
        u8 second = dec_to_u8(gets());
        puts("\nOperator: ");
        char *operator = gets();

        switch (*operator) {
            case '+': result = first + second; break;
            case '-': result = first + second; break;
            case '*': result = first * second; break;
            case '/': result = first / second; break;
            default: puts("Whoops");
        }

        puts("\nResult: ");
        puts(u8_to_dec(result));
    }
    if (!strncmp(command, "mkf", 3)) {
        char filename[MAX_FILE_NAME_SIZE];
        char extension[MAX_FILE_EXTENSION_NAME_SIZE];
        char size[5];
        char dataptr[5];
        buf_input("Filename: ", filename);
        buf_input("Extension: ", extension);
        buf_input("Size: ", size);
        buf_input("Ptr: ", dataptr);
        print_errcode(fs_create_new_file(filename, extension, hex_to_u16(size), (u8 *)hex_to_u16(dataptr)));
    }
    if (!strncmp(command, "find", 4)) {
        errcode_t res = fs_find(input("Filename: "));
        if (res == FS_OK) {
            puts("FS_OK\n FILE SIZE:");
            puts(u16_to_hex(g_returned_file.size));
            putc('\n');
        }
        else
            puts("\nFile not found\n");
    }
}

void legacy_shell_loop(void) {
    while (1)
        legacy_shell();
}