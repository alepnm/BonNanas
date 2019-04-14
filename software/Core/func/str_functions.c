#include <stdbool.h>
#include "str_functions.h"

/*
* function to reverse a string
*/
void fun_reverse(char str[], int len) {
    int start, end;
    char temp;
    for(start=0, end=len-1; start < end; start++, end--) {
        temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
    }
}

int fun_itoa(char* str, int num, int base) {

    int i = 0;
    bool isNegative = false;

    /* A zero is same "0" string in all base */
    if (num == 0) {
        str[i] = '0';
        str[i + 1] = '0';
        return i;
    }

    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    while (num != 0) {

        int rem = num % base;

        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    fun_reverse(str, i);

    return i;
}
