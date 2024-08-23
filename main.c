#include <stdio.h>
#include "library.h"

int main() {
    int step;
    printf("Hello and welcome to our library\n");
    printf("To log in, type 1 and press enter: \n");
    printf("To register, type 2 and press enter: \n");
    scanf("%d", &step);
    getchar();
    printf("\n");
    if (step == 1)
        login();
    if (step == 2)
        create_account();
    else
        printf("Unless you enter the proper number this menu will repeat indefinitely.<3\n");
    main();
    return 0;
}
