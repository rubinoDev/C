#include <stdio.h>
#include <stdbool.h>

void printer(char *string)
{
    char *aux = string;
    printf("PRINTER: ");
    while (*aux != '\0')
    {
        printf("%c", *aux);
        aux++;
    }

    printf("\n");
}

void swap(char *beginPointer, char *finalPointer)
{

    char temp = *beginPointer;
    *beginPointer = *finalPointer;
    *finalPointer = temp;
}

void reverseString(char *s, int sSize)
{
    printer(s);
    char *beginPointer = s;
    char *finalPointer = s + sSize - 1;
    bool isOdd = sSize % 2 != 0;

    printf("Initialized with begin pointer at value: %c, and final pointer at value: %c \n", *beginPointer, *finalPointer);

    int limit = isOdd ? (sSize - 1) / 2 : sSize / 2;

    for (int i = 0; i < limit; i++)
    {
        swap(beginPointer, finalPointer);
        printf("printou %d \n", i);
        beginPointer++;
        finalPointer--;
    }

    printf("Swapped with begin pointer at value: %c, and final pointer at value: %c \n", *beginPointer, *finalPointer);
    printer(s);
}

int main()
{
    char string[] = "Victor Rubino";
    int stringSize = 0;
    char *aux = string;

    while (*aux != '\0')
    {
        stringSize++;
        aux++;
    }

    printf("String size: %d \n", stringSize);
    reverseString(string, stringSize);
    return 0;
}