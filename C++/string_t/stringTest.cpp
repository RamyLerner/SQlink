#include "string_t.h"
#include <cstdio>

int main()
{
    int input = 0;
    char raw[300];

    printf("creating a new object. insert a string:\n");
    scanf("%s", raw);
    String_t s1(raw);
    while (input != -1)
    {
        printf("type 1 for getLength()\ntype 2 for setString()\ntype 3 for getString\ntype 4 to compare\ntype 5 to print\n-1 to exit\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            printf("length: %d\n", s1.getLength());
            break;
        case 2:
            printf("insert string to set:\n");
            scanf("%s", raw);
            s1.setString(raw);
            break;
        case 3:
            printf("%s\n", s1.getString());
            break;
        case 4:
            printf("enter a string to compare with\n");
            scanf("%s", raw);
            if(1){
                String_t s2(raw);
                printf("comparison result: %d\n", s1.compareString(s2));
            }
            break;
        case 5:
            s1.printString();
        case -1:
            break;
        default:
            printf("invalid input\n");
        }
    }
}