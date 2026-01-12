#include "../taulib/globals.h"
#include "../taulib/memorymap.h"
#include "../taulib/stdio.h"
#include "../taulib/string.h"
#include "../taulib/tilegpu.h"
#include "shell/shell.h"
#include "shell/legacy/legacy_shell.h"
#include "filesystem/fs.h"

extern file_t g_returned_file;

#define DISABLE_POST

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
    if (*USER_ASCII == ENTER_KEY)
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

void os_main(void)
{
    restart:
    clear_tty
    if (*USER_READY && *USER_ASCII == ENTER_KEY) {
        clear_tty
        legacy_shell_loop();
        goto restart;
    }
    else {
        shell_loop();
    }
}