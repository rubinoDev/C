#include "victor_birthday.h"
#include <time.h>

char *get_victor_birthday()
{
    struct tm date = {0};
    date.tm_year = 2000 - 1900;
    date.tm_mon = 11; // January = 0
    date.tm_mday = 6;

    return asctime(&date);
}
