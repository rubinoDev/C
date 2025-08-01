#include <stdio.h>

int main()
{
    if (__STDC__)
    {
        printf("The C version is at least C89\n");

#ifdef __STDC_VERSION__
        printf("C standard version: %lu\n", __STDC_VERSION__);
#endif
    }
    else
    {
        printf("Somehow you got ahold of K&R C. Neat!\n");
    }

    return 0;
}

// #include <stdio.h>

// int main(int argc, char** argv) {
//     // Check for C standard version
//     #if __STDC_VERSION__ >=  201710L
//         printf("We are using C18!\n");
//     #elif __STDC_VERSION__ >= 201112L
//         printf("We are using C11!\n");
//     #elif __STDC_VERSION__ >= 199901L
//         printf("We are using C99!\n");
//     #else
//         printf("We are using C89/C90!\n");
//     #endif

//     // Indicate successful execution
//     return 0;
// }