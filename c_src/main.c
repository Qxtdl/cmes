#include "globals.h"
#include "memorymap.h"
#include "stdio.h"
#include "string.h"
#include "tilegpu.h"

//#define DISABLE_POST

void os_main(void);

bool power_on_self_test(void)
{
    /*
        This function performs a series of arithmetic, logical, and comparison tests
        supported for Taurus. If any test fails, it sets POST_FAIL_CAUSE
        to a unique value and returns false. Otherwise, returns true which from there
        the main function can set POST_RESULT to POST_SUCCESS.
    */

    // if the user presses enter during post skip it
    if (*USER_ASCII == '\r')
        return true;

    int a = 12345, b = 6789;
    if ((a + b) != 19134) 
    {
        *POST_FAIL_CAUSE = 1;
        return false;
    }

    // Subtraction
    if ((a - b) != 5556) 
    {
        *POST_FAIL_CAUSE = 2;
        return false;
    }

    // Multiplication
    if ((a << 1) != (a * 2)) 
    {
        *POST_FAIL_CAUSE = 3;
        return false;
    }

    // MODO: DIVISION

    // AND
    if ((a & b) != (12345 & 6789)) 
    {
        *POST_FAIL_CAUSE = 4;
        return false;
    }

    // OR
    if ((a | b) != (12345 | 6789)) 
    {
        *POST_FAIL_CAUSE = 5;
        return false;
    }

    // XOR
    if ((a ^ b) != (12345 ^ 6789)) 
    {
        *POST_FAIL_CAUSE = 6;
        return false;
    }

    // NOT
    if ((~a) != -(a + 1)) 
    {
        *POST_FAIL_CAUSE = 7;
        return false;
    }

    // Left shift
    if ((a << 3) != (12345 * 8)) 
    {
        *POST_FAIL_CAUSE = 8;
        return false;
    }

    // Right shift (logical)
    unsigned int ua = 0xF0000000;
    if ((ua >> 4) != 0x0F000000) 
    {
        *POST_FAIL_CAUSE = 9;
        return false;
    }

    // Right shift (arithmetic)
    int sa = -16;
    if ((sa >> 2) != -4) 
    {
        *POST_FAIL_CAUSE = 10;
        return false;
    }

    // Signed less than
    int x = -5, y = 3;
    if (!(x < y)) 
    {
        *POST_FAIL_CAUSE = 11;
        return false;
    }

    // Unsigned less than
    unsigned int ux = 5, uy = 10;
    if (!(ux < uy)) 
    {
        *POST_FAIL_CAUSE = 12;
        return false;
    }

    // Signed greater than
    if (!(y > x)) 
    {
        *POST_FAIL_CAUSE = 13;
        return false;
    }

    // Unsigned greater than
    if (!(uy > ux)) 
    {
        *POST_FAIL_CAUSE = 14;
        return false;
    }

    // Equality
    if (!(a == 12345)) 
    {
        *POST_FAIL_CAUSE = 15;
        return false;
    }

    // Inequality
    if (!(a != b)) 
    {
        *POST_FAIL_CAUSE = 16;
        return false;
    }

    // Zero test
    int z = 0;
    if (!(z == 0)) 
    {
        *POST_FAIL_CAUSE = 17;
        return false;
    }

    // Negative test
    int neg = -1;
    if (!(neg < 0)) 
    {
        *POST_FAIL_CAUSE = 18;
        return false;
    }

    // Positive test
    int pos = 1;
    if (!(pos > 0)) 
    {
        *POST_FAIL_CAUSE = 19;
        return false;
    }

    return true;
}

int main(void)
{
    *TTY_CLEAR = true;
    *TTY_LOC = 0;
    *TTY_CHAR = 0;
    if (power_on_self_test())
        *POST_RESULT = POST_SUCCESS;
    else
    {
        *POST_RESULT = POST_FAILURE;
        puts("POST FAILED! Halting.");
        while (1);  
    }
    os_main();
}

void eliza()
{
    puts("\nELIZA:How are you feeling today?\n");
    while (1)
    {
        char* input = gets();
        asm volatile ("ebreak");
        if (strstr(input, "bye"))
        {
            clear_tty
            *TTY_LOC = 0;
            return;
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

void fetch_command(void)
{
    puts("\n> ");
    char* command = gets();

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
        eliza();
        return;
    }
    if (strncmp(command, "calc ", 5) == 0)
    {
        u32 x = hex_to_u32(command + 5);
        u32 y = hex_to_u32(command + 5 + 9);
        char *op = command + 5 + 18;

        if (strcmp(op, "+") == 0)
            x = x + y;
        else if (strcmp(op, "-") == 0)
            x = x - y;
        else
        {
            puts("\nUnknown operator. Supported: + -\n");
            return;
        }
        puts("\nResult: 0x");
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
}

void os_main(void)
{
    while (1)
        fetch_command();
}