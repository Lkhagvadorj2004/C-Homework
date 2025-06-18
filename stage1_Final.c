
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define TESTS 7
#define DAYS 6
#define MAX_ROUTINE_LENGTH 100

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

char trainingStatus[8] = { 'N','N','N','N','N','N','N','N' };

const char *fitness_labels[TESTS] = {
    "1-Mile Run (min)",
    "Speed Sprint (s)",
    "Push-ups (min/30 reps)",
    "Squats (min/50 reps)",
    "Arm Strength (min/50 push-ups)",
    "Swimming (min/400m)",
    "Weightlifting (bodyweight x)"
};

const char *milliways_members[MAX_MEMBERS][2] = {
    {"Goeun", "goe"},
    {"Woncheol", "won"},
    {"Youngjin", "you"},
    {"Hyekyung", "hye"},
    {"Arthur", "art"}
};

char health_scores[MAX_MEMBERS][TESTS][20];
char workout_routines[MAX_MEMBERS][DAYS][MAX_ROUTINE_LENGTH];
char diet_plans[MAX_MEMBERS][DAYS][MAX_ROUTINE_LENGTH];

const char *weekdays[DAYS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

void showMainMenu();
void showTrainingMenu();
void setHealth();
void viewHealth();
void setWorkoutRoutine();
void viewWorkoutRoutine();
void setDietPlan();
void viewDietPlan();
int getMemberIndex();

int main() {
    char input[10];
    while (1) {
        showMainMenu();
        printf("\nEnter menu option (1-3), or 0 to quit: ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == '0') break;
        switch (input[0]) {
            case '1': printf("Audition Management Selected\n"); break;
            case '2': showTrainingMenu(); break;
            case '3': printf("Debut Selected\n"); break;
            default: printf("Invalid choice.\n"); break;
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
    char choice[10];
    while (1) {
        printf("\n=== Training Stage 1: Health and Knowledge ===\n");
        printf("A. Enter Physical Condition\n");
        printf("B. View Physical Condition\n");
        printf("C. Set Workout Routine\n");
        printf("D. View Workout Routine\n");
        printf("E. Set Diet Plan\n");
        printf("F. View Diet Plan\n");
        printf("Q. Back to Main Menu\n");
        printf("Select an option: ");
        fgets(choice, sizeof(choice), stdin);
        switch (toupper(choice[0])) {
            case 'A': setHealth(); break;
            case 'B': viewHealth(); break;
            case 'C': setWorkoutRoutine(); break;
            case 'D': viewWorkoutRoutine(); break;
            case 'E': setDietPlan(); break;
            case 'F': viewDietPlan(); break;
            case 'Q': return;
            default: printf("Invalid choice.\n"); break;
        }
    }
}

int getMemberIndex() {
    char name[20];
    printf("Enter member name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, milliways_members[i][0]) == 0) return i;
    }
    printf("Member not found.\n");
    return -1;
}

void setHealth() {
    printf("\n=== Enter Physical Condition ===\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter 7 test results for %s (comma-separated): ", milliways_members[i][0]);
        char input[200];
        fgets(input, sizeof(input), stdin);
        char *token = strtok(input, ",");
        for (int j = 0; j < TESTS && token; j++) {
            strncpy(health_scores[i][j], token, 19);
            token = strtok(NULL, ",");
        }
    }
}

void viewHealth() {
    printf("\n=== View Physical Condition ===\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Member: %s\n", milliways_members[i][0]);
        for (int j = 0; j < TESTS; j++) {
            printf("  %s: %s\n", fitness_labels[j], health_scores[i][j]);
        }
    }
}

void setWorkoutRoutine() {
    int idx = getMemberIndex();
    if (idx == -1) return;
    for (int d = 0; d < DAYS; d++) {
        printf("Enter workout for %s on %s: ", milliways_members[idx][0], weekdays[d]);
        fgets(workout_routines[idx][d], MAX_ROUTINE_LENGTH, stdin);
        workout_routines[idx][d][strcspn(workout_routines[idx][d], "\n")] = '\0';
    }
}

void viewWorkoutRoutine() {
    int idx = getMemberIndex();
    if (idx == -1) return;
    printf("\nWorkout routine for %s:\n", milliways_members[idx][0]);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s\n", weekdays[d], workout_routines[idx][d]);
    }
}

void setDietPlan() {
    int idx = getMemberIndex();
    if (idx == -1) return;
    for (int d = 0; d < DAYS; d++) {
        printf("Enter diet for %s on %s: ", milliways_members[idx][0], weekdays[d]);
        fgets(diet_plans[idx][d], MAX_ROUTINE_LENGTH, stdin);
        diet_plans[idx][d][strcspn(diet_plans[idx][d], "\n")] = '\0';
    }
}

void viewDietPlan() {
    int idx = getMemberIndex();
    if (idx == -1) return;
    printf("\nDiet plan for %s:\n", milliways_members[idx][0]);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s\n", weekdays[d], diet_plans[idx][d]);
    }
}
