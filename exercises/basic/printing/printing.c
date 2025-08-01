#include <stdio.h>
#include <time.h>
#include "victor_birthday.h"

int main()
{
    char myname[] = "Victor Rubiño";
    char *victor_birthday = get_victor_birthday();
    char phone_number[] = "(19) 99699-4646";

    printf("My name: %s\n My birthday: %s \n My phone: %s\n", myname, victor_birthday, phone_number);
    return 0;
}
