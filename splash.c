#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function

#define SPLASH_TEXT "Magrathea, where a shining planet is created in a wasteland with no grass,\n" \
                    "a place where unseen potential is discovered and gems are polished by the hands of experts,\n" \
                    "Welcome to Magrathea."

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void display_splash_screen(const char *name, const char *date) {
    int i, j;
    int width = 105;

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    for (i = 1; i <= 5; i++) {
        for (j = 0; j < i; j++) {
            printf("*");
        }
        int spaces = width - 2 * i;
        printf("%*s", spaces, "");
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("**                                        [Magrathea ver 0.1]                                            **\n");
    printf("***                   Magrathea, where a shining planet is created in a wasteland with no grass,          ***\n");
    printf("****           a place where unseen potential is discovered and gems are polished by the hands of experts, **\n");
    printf("*****                                        Welcome to Magrathea.                                          *\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("=============================================================================================================\n");
}

int main() {
    char name[50], date[15];
    
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%14s", date);
    printf("[Please enter your name]: ");
    scanf("%49s", name);
    
    printf("\n**The input has been processed successfully.**\n");
    sleep(3);
    clear_screen();
    
    display_splash_screen(name, date);
    
    return 0;
}