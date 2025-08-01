#include <stdio.h>

int main()
{
    while (1)
    {
        char user_input[100];
        char *ptr;

        printf("Sua string: \n");
        scanf("%s", user_input);

        char *original_char = user_input;
        ptr = user_input;

        printf("String original:");
        while (*ptr != '\0')
        {
            printf("%c", *ptr);
            ptr++;
        }

        printf("\n");

        printf("String invertida:");
        while (ptr >= original_char)
        {
            ptr--;
            printf("%c", *ptr);
        }

        printf("\n");
    }

    return 0;
};