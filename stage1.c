#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1D arrays for menu text
const char *mainMenu[] = {
    "1. Audition Management",
    "2. Training",
    "3. Debut"
};

const char *trainingStages[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Training status: 'N' = Not attempted, 'P' = Passed, 'F' = Failed
char trainingStatus[8] = { 'N','N','N','N','N','N','N','N' };

// Function declarations
void showMainMenu();
void showTrainingMenu();
void handleTrainingStage(int stage);
void clearInputBuffer();

int main() {
    char input[10];

    while (1) {
        showMainMenu();
        printf("\nEnter menu option (1-3), or 0/Q/q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == '\n' || tolower(input[0]) == 'q') {
            printf("Exiting program. Goodbye.\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf("Audition Management selected.\n\n");
                break;
            case '2':
                showTrainingMenu();
                break;
            case '3':
                printf("Debut process selected.\n\n");
                break;
            default:
                printf("Invalid selection. Try again.\n\n");
        }
    }

    return 0;
}

void showMainMenu() {
    printf("\n=== Magrathea Main Menu ===\n");
    for (int i = 0; i < 3; i++) {
        printf("%s\n", mainMenu[i]);
    }
}

void showTrainingMenu() {
    char input[10];

    while (1) {
        printf("\n=== Training Stages ===\n");
        for (int i = 0; i < 8; i++) {
            printf("%d. %s [%c]\n", i + 1, trainingStages[i], trainingStatus[i]);
        }

        printf("Select a stage (1-8), or 0/Q/q to go back: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == '\n' || tolower(input[0]) == 'q') {
            break;
        }

        int stage = input[0] - '0';

        if (stage < 1 || stage > 8) {
            printf("Invalid stage. Try again.\n");
            continue;
        }

        // Stage access rules
        if (stage == 1 || stage == 2) {
            if (stage == 2 && trainingStatus[0] != 'P') {
                printf("Stage 1 must be passed before attempting Stage 2.\n");
                continue;
            }
        } else {
            if (trainingStatus[0] != 'P' || trainingStatus[1] != 'P') {
                printf("Stages 1 and 2 must be passed before accessing Stages 3-8.\n");
                continue;
            }
        }

        if (trainingStatus[stage - 1] == 'P') {
            printf("Stage %d already completed and passed. Cannot re-select.\n", stage);
            continue;
        }

        handleTrainingStage(stage);
    }
}

void handleTrainingStage(int stage) {
    char input[10];

    printf("\nWould you like to enter the evaluation result for \"%s\"? (Y/N): ", trainingStages[stage - 1]);
    fgets(input, sizeof(input), stdin);

    if (toupper(input[0]) == 'Y') {
        printf("Did you complete the training and pass the certification? (Y/N): ");
        fgets(input, sizeof(input), stdin);

        if (toupper(input[0]) == 'Y') {
            trainingStatus[stage - 1] = 'P';
            printf("Stage %d marked as Passed.\n", stage);
        } else {
            trainingStatus[stage - 1] = 'F';
            printf("Stage %d marked as Failed.\n", stage);
        }
    } else {
        printf("Returning to training menu.\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
