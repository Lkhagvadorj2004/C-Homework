#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_STRING 512
#define FIELD_COUNT 7

char *fields[FIELD_COUNT] = {
    "Name", "Gender", "Affiliation", "Title", "Specialty", "Email", "Phone"
};

char judges_array[MAX_JUDGES][MAX_STRING];

int main() {
    char project_name[100];
    int total_judges = 0;
    int selected_members = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = 0;  // Remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar(); // Consume leftover newline

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // Consume leftover newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n\n");

    for (int i = 0; i < total_judges; i++) {
        char buffer[MAX_STRING] = "";
        char input[128];

        printf("Judge %d:\n", i + 1);
        for (int j = 0; j < FIELD_COUNT; j++) {
            printf("  %s: ", fields[j]);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;  // Remove newline

            if (strlen(input) == 0) {
                printf("  The input for %s is empty. Please re-enter this judge.\n", fields[j]);
                j = -1;
                memset(buffer, 0, sizeof(buffer));
                continue;
            }

            char entry[150];
            snprintf(entry, sizeof(entry), "%s: %s", fields[j], input);
            strcat(buffer, entry);
            if (j < FIELD_COUNT - 1)
                strcat(buffer, ", ");
        }

        strncpy(judges_array[i], buffer, MAX_STRING - 1);
        printf("\n");
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    printf("Should we check the judge information? (Y/N): ");
    char answer;
    scanf(" %c", &answer);

    if (answer == 'Y') {
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            printf("[Judge %d]\n", i + 1);

            char temp[MAX_STRING];
            strcpy(temp, judges_array[i]);
            char *token = strtok(temp, ",");

            while (token != NULL) {
                printf("%s\n", token);
                token = strtok(NULL, ",");
            }

            printf("-----------------------------------\n");
        }
    }

    return 0;
}
