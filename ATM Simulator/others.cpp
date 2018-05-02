#include "others.h"

char getch()
{
    char c;
    system("stty -echo");
    system("stty -icanon");
    c=getchar();
    system("stty icanon");
    system("stty echo");
    return c;
}

std::string toString(int num){
    char s[20];
    sprintf(s, "%d", num);
    std::string str;
    str += s;
    return str;
}

std::string toStringFormat(int num, int len){
    std::string str(len, '0');
    for(int i = len - 1; i >= 0; i--){
        if(num == 0){
            break;
        }
        str[i] = num % 10 + '0';
        num /= 10;
    }
    return str;
}
