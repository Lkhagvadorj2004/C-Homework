#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INFO_LEN 512

char judges_array[MAX_JUDGES][MAX_INFO_LEN];

void display_judges(int total_judges, char *project_name) {
    printf("####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");
    for (int i = 0; i < total_judges; i++) {
        printf("[Judge %d]\n", i + 1);

        char *token;
        token = strtok(judges_array[i], ",");
        int count = 0;
        while (token != NULL) {
            switch (count) {
                case 0: printf("Name: %s\n", token + 6); break; // Skip "Name: "
                case 1: printf("Gender: %s\n", token + 8); break;
                case 2: printf("Affiliation: %s\n", token + 13); break;
                case 3: printf("Title: %s\n", token + 8); break;
                case 4: printf("Expertise: %s\n", token + 11); break;
                case 5: printf("Email: %s\n", token + 7); break;
                case 6: printf("Phone: %s\n", token + 7); break;
                default: break;
            }
            token = strtok(NULL, ",");
            count++;
        }

        if (count != 7) {
            printf("The input items are incorrect.\n");
        }

        printf("-----------------------------------\n");
    }
}

int main() {
    char project_name[100];
    int total_judges;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");
    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar(); // consume newline

    printf("Number of Selected Members: 4\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int i = 0;
    while (i < total_judges) {
        printf("Judge %d: ", i + 1);
        fgets(judges_array[i], MAX_INFO_LEN, stdin);
        if (strchr(judges_array[i], '\n') == NULL) while (getchar() != '\n'); // clear extra input
        judges_array[i][strcspn(judges_array[i], "\n")] = '\0';

        // Check if 7 items are input
        char copy[MAX_INFO_LEN];
        strcpy(copy, judges_array[i]);
        int count = 0;
        char *token = strtok(copy, ",");
        while (token != NULL) {
            count++;
            token = strtok(NULL, ",");
        }

        if (count != 7) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        i++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("\"Should we check the judge information?\" ");

    char check;
    scanf(" %c", &check);
    if (check == 'Y') {
        printf("[%s] Should we check the judge information? Y\n", project_name);
        display_judges(total_judges, project_name);
    }

    return 0;
}
